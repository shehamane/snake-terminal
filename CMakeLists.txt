cmake_minimum_required(VERSION 3.24)
project(snake_terminal)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_EXE main.cpp)
set(SOURCE_LIB src/lib/Vector2D.cpp src/lib/Level.cpp src/lib/Snake.cpp src/lib/Controller.cpp)

add_library(MAIN STATIC ${SOURCE_LIB})
add_executable(main ${SOURCE_EXE})

target_link_libraries(main MAIN)