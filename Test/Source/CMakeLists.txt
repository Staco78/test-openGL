include_directories(${CMAKE_SOURCE_DIR}/Test/Header)

file(GLOB_RECURSE SRCS *.cpp *.vertex *.fragment)
file(GLOB_RECURSE HDRS *.h)

add_executable(Test ${SRCS} ${HDRS})
target_link_libraries(Test glfw3 glew32)