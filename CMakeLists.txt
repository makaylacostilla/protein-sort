cmake_minimum_required(VERSION 3.24)
project(protein_sort)

set(CMAKE_CXX_STANDARD 11)

add_executable(protein_sort main.cpp Parser.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include/SFML)
target_link_libraries(protein_sort sfml-system sfml-window sfml-graphics sfml-audio)
