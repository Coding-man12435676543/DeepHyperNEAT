cmake_minimum_required(VERSION 3.16)
project(deephyperneat_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(deephyperneat
    src/activations.cpp
    src/util.cpp
    src/phenomes.cpp
    src/genome.cpp
    src/species.cpp
    src/stagnation.cpp
    src/reproduction.cpp
    src/decode.cpp
    src/population.cpp
    src/reporters.cpp
    src/visualize.cpp
)

target_include_directories(deephyperneat PUBLIC include)

add_executable(xor_example examples/xor_main.cpp)
target_link_libraries(xor_example PRIVATE deephyperneat)
