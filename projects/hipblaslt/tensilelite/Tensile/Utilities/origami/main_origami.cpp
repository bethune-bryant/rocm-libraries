#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>

#include <Tensile/analytical/Hardware.hpp>
#include <Tensile/analytical/Utils.hpp>

int main(int argc, char* argv[]) {
    if (argc != 8) {
        std::cerr << "Usage: " << argv[0] << " <element_size> <m> <n> <k> <transA> <transB>" << std::endl;
        return 1;
    }

    size_t element_size = std::stoul(argv[1]);
    size_t m = std::stoul(argv[2]);
    size_t n = std::stoul(argv[3]);
    size_t k = std::stoul(argv[4]);
    bool transA = std::string(argv[5]) == "true";
    bool transB = std::string(argv[6]) == "true";
    size_t iters = std::stoul(argv[7]);
    float alpha = 1;
    float beta = 0;

    auto Hardware = TensileLite::analytical::Hardware::getHardwareForDevice(0);
    Hardware.print();

    std::vector<std::tuple<size_t, size_t, size_t, size_t, size_t, size_t, size_t>> tile_list;
    tile_list.emplace_back(256, 256, 32, 16, 16, 16, 1);
    tile_list.emplace_back(256, 224, 32, 16, 16, 16, 1);
    tile_list.emplace_back(256, 192, 32, 16, 16, 16, 1);
    tile_list.emplace_back(256, 160, 32, 16, 16, 16, 1);
    tile_list.emplace_back(256, 128, 32, 16, 16, 16, 1);
    tile_list.emplace_back(256, 96, 32, 16, 16, 16, 1);
    tile_list.emplace_back(256, 64, 32, 16, 16, 16, 1);
    tile_list.emplace_back(256, 32, 32, 16, 16, 16, 1);
    tile_list.emplace_back(224, 256, 32, 16, 16, 16, 1);
    tile_list.emplace_back(224, 224, 32, 16, 16, 16, 1);
    tile_list.emplace_back(224, 192, 32, 16, 16, 16, 1);
    tile_list.emplace_back(224, 160, 32, 16, 16, 16, 1);
    tile_list.emplace_back(224, 128, 32, 16, 16, 16, 1);
    tile_list.emplace_back(224, 96, 32, 16, 16, 16, 1);
    tile_list.emplace_back(224, 64, 32, 16, 16, 16, 1);
    tile_list.emplace_back(224, 32, 32, 16, 16, 16, 1);
    tile_list.emplace_back(192, 256, 32, 16, 16, 16, 1);
    tile_list.emplace_back(192, 224, 32, 16, 16, 16, 1);
    tile_list.emplace_back(192, 192, 32, 16, 16, 16, 1);
    tile_list.emplace_back(192, 160, 32, 16, 16, 16, 1);
    tile_list.emplace_back(192, 128, 32, 16, 16, 16, 1);
    tile_list.emplace_back(192, 96, 32, 16, 16, 16, 1);
    tile_list.emplace_back(192, 64, 32, 16, 16, 16, 1);
    tile_list.emplace_back(192, 32, 32, 16, 16, 16, 1);
    tile_list.emplace_back(160, 256, 32, 16, 16, 16, 1);
    tile_list.emplace_back(160, 224, 32, 16, 16, 16, 1);
    tile_list.emplace_back(160, 192, 32, 16, 16, 16, 1);
    tile_list.emplace_back(160, 160, 32, 16, 16, 16, 1);
    tile_list.emplace_back(160, 128, 32, 16, 16, 16, 1);
    tile_list.emplace_back(160, 96, 32, 16, 16, 16, 1);
    tile_list.emplace_back(160, 64, 32, 16, 16, 16, 1);
    tile_list.emplace_back(160, 32, 32, 16, 16, 16, 1);
    tile_list.emplace_back(128, 256, 32, 16, 16, 16, 1);
    tile_list.emplace_back(128, 224, 32, 16, 16, 16, 1);
    tile_list.emplace_back(128, 192, 32, 16, 16, 16, 1);
    tile_list.emplace_back(128, 160, 32, 16, 16, 16, 1);
    tile_list.emplace_back(128, 128, 32, 16, 16, 16, 1);
    tile_list.emplace_back(128, 96, 32, 16, 16, 16, 1);
    tile_list.emplace_back(128, 64, 32, 16, 16, 16, 1);
    tile_list.emplace_back(128, 32, 32, 16, 16, 16, 1);
    tile_list.emplace_back(96, 256, 32, 16, 16, 16, 1);
    tile_list.emplace_back(96, 224, 32, 16, 16, 16, 1);
    tile_list.emplace_back(96, 192, 32, 16, 16, 16, 1);
    tile_list.emplace_back(96, 160, 32, 16, 16, 16, 1);
    tile_list.emplace_back(96, 128, 32, 16, 16, 16, 1);
    tile_list.emplace_back(96, 96, 32, 16, 16, 16, 1);
    tile_list.emplace_back(96, 64, 32, 16, 16, 16, 1);
    tile_list.emplace_back(96, 32, 32, 16, 16, 16, 1);
    tile_list.emplace_back(64, 256, 32, 16, 16, 16, 1);
    tile_list.emplace_back(64, 224, 32, 16, 16, 16, 1);
    tile_list.emplace_back(64, 192, 32, 16, 16, 16, 1);
    tile_list.emplace_back(64, 160, 32, 16, 16, 16, 1);
    tile_list.emplace_back(64, 128, 32, 16, 16, 16, 1);
    tile_list.emplace_back(64, 96, 32, 16, 16, 16, 1);
    tile_list.emplace_back(64, 64, 32, 16, 16, 16, 1);
    tile_list.emplace_back(64, 32, 32, 16, 16, 16, 1);
    tile_list.emplace_back(32, 256, 32, 16, 16, 16, 1);
    tile_list.emplace_back(32, 224, 32, 16, 16, 16, 1);
    tile_list.emplace_back(32, 192, 32, 16, 16, 16, 1);
    tile_list.emplace_back(32, 160, 32, 16, 16, 16, 1);
    tile_list.emplace_back(32, 128, 32, 16, 16, 16, 1);
    tile_list.emplace_back(32, 96, 32, 16, 16, 16, 1);
    tile_list.emplace_back(32, 64, 32, 16, 16, 16, 1);
    tile_list.emplace_back(32, 32, 32, 16, 16, 16, 1);
    tile_list.emplace_back(256, 240, 32, 16, 16, 16, 1);
    tile_list.emplace_back(256, 208, 32, 16, 16, 16, 1);
    tile_list.emplace_back(256, 176, 32, 16, 16, 16, 1);
    tile_list.emplace_back(256, 144, 32, 16, 16, 16, 1);
    tile_list.emplace_back(256, 112, 32, 16, 16, 16, 1);
    tile_list.emplace_back(256, 80, 32, 16, 16, 16, 1);
    tile_list.emplace_back(256, 48, 32, 16, 16, 16, 1);
    tile_list.emplace_back(256, 16, 32, 16, 16, 16, 1);
    tile_list.emplace_back(240, 256, 32, 16, 16, 16, 1);
    tile_list.emplace_back(208, 256, 32, 16, 16, 16, 1);
    tile_list.emplace_back(176, 256, 32, 16, 16, 16, 1);
    tile_list.emplace_back(144, 256, 32, 16, 16, 16, 1);
    tile_list.emplace_back(112, 256, 32, 16, 16, 16, 1);
    tile_list.emplace_back(80, 256, 32, 16, 16, 16, 1);
    tile_list.emplace_back(48, 256, 32, 16, 16, 16, 1);
    tile_list.emplace_back(16, 256, 32, 16, 16, 16, 1);
    tile_list.emplace_back(256, 224, 64, 16, 16, 16, 1);
    tile_list.emplace_back(256, 192, 64, 16, 16, 16, 1);
    tile_list.emplace_back(256, 160, 64, 16, 16, 16, 1);
    tile_list.emplace_back(256, 128, 64, 16, 16, 16, 1);
    tile_list.emplace_back(256, 96, 64, 16, 16, 16, 1);
    tile_list.emplace_back(256, 64, 64, 16, 16, 16, 1);
    tile_list.emplace_back(256, 32, 64, 16, 16, 16, 1);
    tile_list.emplace_back(224, 256, 64, 16, 16, 16, 1);
    tile_list.emplace_back(224, 224, 64, 16, 16, 16, 1);
    tile_list.emplace_back(224, 192, 64, 16, 16, 16, 1);
    tile_list.emplace_back(224, 160, 64, 16, 16, 16, 1);
    tile_list.emplace_back(224, 128, 64, 16, 16, 16, 1);
    tile_list.emplace_back(224, 96, 64, 16, 16, 16, 1);
    tile_list.emplace_back(224, 64, 64, 16, 16, 16, 1);
    tile_list.emplace_back(224, 32, 64, 16, 16, 16, 1);
    tile_list.emplace_back(192, 256, 64, 16, 16, 16, 1);
    tile_list.emplace_back(192, 224, 64, 16, 16, 16, 1);
    tile_list.emplace_back(192, 192, 64, 16, 16, 16, 1);
    tile_list.emplace_back(192, 160, 64, 16, 16, 16, 1);
    tile_list.emplace_back(192, 128, 64, 16, 16, 16, 1);
    tile_list.emplace_back(192, 96, 64, 16, 16, 16, 1);
    tile_list.emplace_back(192, 64, 64, 16, 16, 16, 1);
    tile_list.emplace_back(192, 32, 64, 16, 16, 16, 1);
    tile_list.emplace_back(160, 256, 64, 16, 16, 16, 1);
    tile_list.emplace_back(160, 224, 64, 16, 16, 16, 1);
    tile_list.emplace_back(160, 192, 64, 16, 16, 16, 1);
    tile_list.emplace_back(160, 160, 64, 16, 16, 16, 1);
    tile_list.emplace_back(160, 128, 64, 16, 16, 16, 1);
    tile_list.emplace_back(160, 96, 64, 16, 16, 16, 1);
    tile_list.emplace_back(160, 64, 64, 16, 16, 16, 1);
    tile_list.emplace_back(160, 32, 64, 16, 16, 16, 1);
    tile_list.emplace_back(128, 256, 64, 16, 16, 16, 1);
    tile_list.emplace_back(128, 224, 64, 16, 16, 16, 1);
    tile_list.emplace_back(128, 192, 64, 16, 16, 16, 1);
    tile_list.emplace_back(128, 160, 64, 16, 16, 16, 1);
    tile_list.emplace_back(128, 128, 64, 16, 16, 16, 1);
    tile_list.emplace_back(128, 96, 64, 16, 16, 16, 1);
    tile_list.emplace_back(128, 64, 64, 16, 16, 16, 1);
    tile_list.emplace_back(128, 32, 64, 16, 16, 16, 1);
    tile_list.emplace_back(96, 256, 64, 16, 16, 16, 1);
    tile_list.emplace_back(96, 224, 64, 16, 16, 16, 1);
    tile_list.emplace_back(96, 192, 64, 16, 16, 16, 1);
    tile_list.emplace_back(96, 160, 64, 16, 16, 16, 1);
    tile_list.emplace_back(96, 128, 64, 16, 16, 16, 1);
    tile_list.emplace_back(96, 96, 64, 16, 16, 16, 1);
    tile_list.emplace_back(96, 64, 64, 16, 16, 16, 1);
    tile_list.emplace_back(96, 32, 64, 16, 16, 16, 1);
    tile_list.emplace_back(64, 256, 64, 16, 16, 16, 1);
    tile_list.emplace_back(64, 224, 64, 16, 16, 16, 1);
    tile_list.emplace_back(64, 192, 64, 16, 16, 16, 1);
    tile_list.emplace_back(64, 160, 64, 16, 16, 16, 1);
    tile_list.emplace_back(64, 128, 64, 16, 16, 16, 1);
    tile_list.emplace_back(64, 96, 64, 16, 16, 16, 1);
    tile_list.emplace_back(64, 64, 64, 16, 16, 16, 1);
    tile_list.emplace_back(64, 32, 64, 16, 16, 16, 1);
    tile_list.emplace_back(32, 256, 64, 16, 16, 16, 1);
    tile_list.emplace_back(32, 224, 64, 16, 16, 16, 1);
    tile_list.emplace_back(32, 192, 64, 16, 16, 16, 1);
    tile_list.emplace_back(32, 160, 64, 16, 16, 16, 1);
    tile_list.emplace_back(32, 128, 64, 16, 16, 16, 1);
    tile_list.emplace_back(32, 96, 64, 16, 16, 16, 1);
    tile_list.emplace_back(32, 64, 64, 16, 16, 16, 1);
    tile_list.emplace_back(32, 32, 64, 16, 16, 16, 1);
    tile_list.emplace_back(256, 208, 64, 16, 16, 16, 1);
    tile_list.emplace_back(256, 176, 64, 16, 16, 16, 1);
    tile_list.emplace_back(256, 144, 64, 16, 16, 16, 1);
    tile_list.emplace_back(256, 112, 64, 16, 16, 16, 1);
    tile_list.emplace_back(256, 80, 64, 16, 16, 16, 1);
    tile_list.emplace_back(256, 48, 64, 16, 16, 16, 1);
    tile_list.emplace_back(256, 16, 64, 16, 16, 16, 1);
    tile_list.emplace_back(208, 256, 64, 16, 16, 16, 1);
    tile_list.emplace_back(176, 256, 64, 16, 16, 16, 1);
    tile_list.emplace_back(144, 256, 64, 16, 16, 16, 1);
    tile_list.emplace_back(112, 256, 64, 16, 16, 16, 1);
    tile_list.emplace_back(80, 256, 64, 16, 16, 16, 1);
    tile_list.emplace_back(48, 256, 64, 16, 16, 16, 1);
    tile_list.emplace_back(16, 256, 64, 16, 16, 16, 1);
    tile_list.emplace_back(192, 32, 128, 16, 16, 16, 1);
    tile_list.emplace_back(160, 64, 128, 16, 16, 16, 1);
    tile_list.emplace_back(160, 32, 128, 16, 16, 16, 1);
    tile_list.emplace_back(128, 96, 128, 16, 16, 16, 1);
    tile_list.emplace_back(128, 64, 128, 16, 16, 16, 1);
    tile_list.emplace_back(128, 32, 128, 16, 16, 16, 1);
    tile_list.emplace_back(96, 128, 128, 16, 16, 16, 1);
    tile_list.emplace_back(96, 96, 128, 16, 16, 16, 1);
    tile_list.emplace_back(96, 64, 128, 16, 16, 16, 1);
    tile_list.emplace_back(96, 32, 128, 16, 16, 16, 1);
    tile_list.emplace_back(64, 160, 128, 16, 16, 16, 1);
    tile_list.emplace_back(64, 128, 128, 16, 16, 16, 1);
    tile_list.emplace_back(64, 96, 128, 16, 16, 16, 1);
    tile_list.emplace_back(64, 64, 128, 16, 16, 16, 1);
    tile_list.emplace_back(64, 32, 128, 16, 16, 16, 1);
    tile_list.emplace_back(32, 192, 128, 16, 16, 16, 1);
    tile_list.emplace_back(32, 160, 128, 16, 16, 16, 1);
    tile_list.emplace_back(32, 128, 128, 16, 16, 16, 1);
    tile_list.emplace_back(32, 96, 128, 16, 16, 16, 1);
    tile_list.emplace_back(32, 64, 128, 16, 16, 16, 1);
    tile_list.emplace_back(32, 32, 128, 16, 16, 16, 1);
    tile_list.emplace_back(256, 256, 64, 16, 16, 16, 1);

    {
        auto   selected_tiles = TensileLite::analytical::select_best_macro_tile_size(m, n, k, 1, transA, transB, Hardware, tile_list, element_size, element_size, element_size, 1, 0.8, true, true, 6);
        for(auto& tile : selected_tiles)
        {
            std::cout << "(";
            std::cout << std::get<0>(tile) << ", ";
            std::cout << std::get<1>(tile) << ", ";
            std::cout << std::get<2>(tile) << ", ";
            std::cout << std::get<3>(tile) << ", ";
            std::cout << std::get<4>(tile) << ", ";
            std::cout << std::get<5>(tile) << ", ";
            std::cout << std::get<6>(tile) << ", ";
            std::cout << ") , ";
        }
        std::cout << std::endl;
    }

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < iters; i++)
    {
        auto   selected_tiles = TensileLite::analytical::select_best_macro_tile_size(m, n, k, 1, transA, transB, Hardware, tile_list, element_size, element_size, element_size, 1, 0.8, false, false, 6);
    }
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    std::chrono::duration<double, std::micro> duration = end - start;

    // Report the runtime
    std::cout << "Average Runtime over " << iters << ": " << duration.count() / iters << " us" << std::endl;


    return 0;
}
