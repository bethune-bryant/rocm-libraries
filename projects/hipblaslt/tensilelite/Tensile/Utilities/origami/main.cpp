#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <chrono>

#include <hipblaslt/hipblaslt.h>
#include <hipblaslt/hipblaslt-ext.hpp>

#include <Tensile/analytical/Hardware.hpp>
#include <Tensile/analytical/Utils.hpp>

#ifndef HIP_CHECK_EXC
#define HIP_CHECK_EXC(expr)                                                                       \
    do                                                                                            \
    {                                                                                             \
        hipError_t e = (expr);                                                                    \
        if(e)                                                                                     \
        {                                                                                         \
            const char*        errName = hipGetErrorName(e);                                      \
            const char*        errMsg  = hipGetErrorString(e);                                    \
            std::ostringstream msg;                                                               \
            msg << "Error " << e << "(" << errName << ") " << __FILE__ << ":" << __LINE__ << ": " \
                << std::endl                                                                      \
                << #expr << std::endl                                                             \
                << errMsg << std::endl;                                                           \
            throw std::runtime_error(msg.str());                                                  \
        }                                                                                         \
    } while(0)
#endif
    

#ifndef CHECK_HIPBLASLT_ERROR
#define CHECK_HIPBLASLT_ERROR(error)                                                      \
    if(error != HIPBLAS_STATUS_SUCCESS)                                                   \
    {                                                                                     \
        fprintf(stderr, "hipBLASLt error(Err=%d) at %s:%d\n", error, __FILE__, __LINE__); \
        fprintf(stderr, "\n");                                                            \
        exit(EXIT_FAILURE);                                                               \
    }
#endif

int main(int argc, char* argv[]) {
    if (argc > 9 || argc < 8) {
        std::cerr << "Usage: " << argv[0] << " <element_size> <m> <n> <k> <transA> <transB>" << std::endl;
        return 1;
    }

    size_t element_size = std::stoul(argv[1]);
    size_t m = std::stoul(argv[2]);
    size_t n = std::stoul(argv[3]);
    size_t k = std::stoul(argv[4]);
    hipblasOperation_t transA = std::string(argv[5]) == "true" ? HIPBLAS_OP_T: HIPBLAS_OP_N;
    hipblasOperation_t transB = std::string(argv[6]) == "true" ? HIPBLAS_OP_T: HIPBLAS_OP_N;
    size_t iters = std::stoul(argv[7]);
    size_t warmups = 2;
    if(argc > 8) warmups = std::stoul(argv[8]);
    float alpha = 1;
    float beta = 0;

    size_t maxM = m + iters + warmups;
    size_t maxN = n;
    size_t maxK = k;

    void* d_A;
    HIP_CHECK_EXC(hipMalloc(&d_A, maxM * maxK * sizeof(float) / 2));
    void* d_B;
    HIP_CHECK_EXC(hipMalloc(&d_B, maxN * maxK * sizeof(float) / 2));
    void* d_C;
    HIP_CHECK_EXC(hipMalloc(&d_C, maxM * maxN * sizeof(float) / 2));
    void* d_D;
    HIP_CHECK_EXC(hipMalloc(&d_D, maxM * maxN * sizeof(float) / 2));



    std::shared_ptr<hipblasLtHandle_t> hipblasLtHandle  = std::make_shared<hipblasLtHandle_t>();
    hipblasLtCreate(&(*hipblasLtHandle));

    hipblaslt_ext::GemmPreference gemmPref;
    gemmPref.setMaxWorkspaceBytes(134217728);
    
    std::vector<std::shared_ptr<hipblaslt_ext::Gemm>> gemms;

    for(int i = 0; i < iters + warmups; i++)
    {
        std::shared_ptr<hipblaslt_ext::Gemm> gemm = std::make_shared<hipblaslt_ext::Gemm>(
            *hipblasLtHandle, transA, transB, HIP_R_16F, HIP_R_16F, HIP_R_16F, HIP_R_16F, HIPBLAS_COMPUTE_32F);

        hipblaslt_ext::GemmEpilogue
            epilogue; // No action needed, default is HIPBLASLT_EPILOGUE_DEFAULT. (Gemm only)
        hipblaslt_ext::GemmInputs inputs;
        inputs.setA(d_A);
        inputs.setB(d_B);
        inputs.setC(d_C);
        inputs.setD(d_D);
        inputs.setAlpha(&alpha);
        inputs.setBeta(&beta);
        gemm->setProblem(m + i, n, k, 1, epilogue, inputs);
        
        gemms.emplace_back(gemm);
    }

    const int                                     request_solutions = 1;
    std::vector<hipblasLtMatmulHeuristicResult_t> heuristicResult;

    
    auto initial_start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < warmups; i++)
    {
        CHECK_HIPBLASLT_ERROR(gemms[i]->algoGetHeuristic(request_solutions, gemmPref, heuristicResult));
    }

    auto initial_end = std::chrono::high_resolution_clock::now();

    auto start = std::chrono::high_resolution_clock::now();

    for(int i = warmups; i < iters + warmups; i++)
    {
        CHECK_HIPBLASLT_ERROR(gemms[i]->algoGetHeuristic(request_solutions, gemmPref, heuristicResult));
    }


    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    std::chrono::duration<double, std::micro> initial_duration = initial_end - initial_start;
    std::chrono::duration<double, std::micro> duration = end - start;

    // Report the runtime
    std::cout << "Average Warmup Runtime: " << initial_duration.count() / warmups << " us" << std::endl;
    std::cout << "Average Runtime over " << iters << ": " << duration.count() / iters << " us" << std::endl;


    return 0;
}
