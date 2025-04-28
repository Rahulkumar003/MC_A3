cmake_minimum_required(VERSION 3.10.2)

# Include Eigen header-only library
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/eigen)

# Add native library
add_library(matrix_operations SHARED
        matrix_operations.cpp)

# Link libraries needed for matrix operations
target_link_libraries(matrix_operations
        android
        log)