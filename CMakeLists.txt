cmake_minimum_required(VERSION 3.18)

project(Test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin)
link_libraries(openGl32.lib assimp-vc140-mt.lib)
link_directories(${CMAKE_SOURCE_DIR}/Lib)
include_directories(${CMAKE_SOURCE_DIR}/ThirdParty)

add_subdirectory(Test/Source)