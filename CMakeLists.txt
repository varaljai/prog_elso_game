cmake_minimum_required(VERSION 3.30.5)
project(CLionGraphicsKit)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_library(graphics graphics.cpp)

include_directories(include)
link_directories(lib)

target_link_libraries( graphics SDL2 SDL2.dll SDL2main SDL2_ttf SDL2_ttf.dll)


add_executable(CLionGraphicsKit main.cpp
        vec2.hpp
        ball.hpp
        consts.hpp
        model.hpp
        block.hpp
        paddle.hpp
        normal_block.hpp)
target_link_libraries(CLionGraphicsKit graphics)
