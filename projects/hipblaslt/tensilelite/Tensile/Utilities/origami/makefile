# Define the compiler
CXX = /opt/rocm/bin/hipcc

#cpp-security-extended

#INCLUDES = -I../tensilelite/Tensile/Source/lib/include -I/opt/rocm/include -I/home/brnelson/git/hipBLASLt/build/release/hipblaslt-install/include
STANDALONE_INCLUDES = -I../../Source/lib/include

# Define the compiler flags
#CXXFLAGS = -O3 -Wall -std=c++17 $(INCLUDES) -L/opt/rocm/lib  -gdwarf-4 -L/home/brnelson/git/hipBLASLt/build/release/hipblaslt-install/lib -lhipblaslt -D__HIP_PLATFORM_AMD__
STANDALONE_CXXFLAGS = -O3 -Wall -fopenmp -std=c++17 $(STANDALONE_INCLUDES) -gdwarf-4

# Define the target executable
#TARGET = hipblaslt_client
STANDALONE_TARGET = origami_client

# Define the source files
#SRCS = ./main.cpp
STANDALONE_SRCS = ./main_origami.cpp $(wildcard ../../Source/lib/source/analytical/*.cpp)

# Define the object files
#OBJS = $(SRCS:.cpp=.o)
STANDALONE_OBJS = $(STANDALONE_SRCS:.cpp=.o)
STANDALONE_OBJS := $(addprefix ./, $(notdir $(STANDALONE_OBJS)))


# Rule to build the target executable
#$(TARGET): $(OBJS)
#	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(STANDALONE_TARGET): $(STANDALONE_OBJS)
	$(CXX) $(STANDALONE_CXXFLAGS) -o $(STANDALONE_TARGET) $(STANDALONE_OBJS)

# Rule to build the object files
#$(OBJS): %.o: %.cpp
#	$(CXX) $(CXXFLAGS) -c $< -o $@


./%.o: ../../Source/lib/source/analytical/%.cpp
	$(CXX) $(STANDALONE_CXXFLAGS) -c $< -o $@


./%.o: %.cpp
	$(CXX) $(STANDALONE_CXXFLAGS) -c $< -o $@


#all: $(TARGET) $(STANDALONE_TARGET)
all: $(STANDALONE_TARGET)

# Rule to clean the build directory
clean:
	rm -f $(OBJS) $(TARGET) $(STANDALONE_OBJS) $(STANDALONE_TARGET)
