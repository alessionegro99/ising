cmake_minimum_required(VERSION 3.10)
project(MyProject CXX)

# Allow setting DIM from the command line, defaulting to 10 if not set
set(DIM 2 CACHE STRING "Dimension value")

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source and include directories
set(SRC_DIR src)
set(INCLUDE_DIR include)
set(LIB_DIR lib)
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp" "${LIB_DIR}/*.cpp")

# Create the executable
add_executable(main ${SRC_FILES})

# Add include directories
target_include_directories(main PRIVATE ${INCLUDE_DIR})

# Pass DIM as a preprocessor definition
target_compile_definitions(main PRIVATE DIM=${DIM})

