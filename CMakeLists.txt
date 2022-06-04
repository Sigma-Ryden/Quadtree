cmake_minimum_required(VERSION 3.5)

project(Quadtree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(src)

add_executable(${PROJECT_NAME} main.cpp
    src/Quadtree.cpp
    include/Object/Base.hpp
    include/Object/Rectangle.hpp
    include/Object/Circle.hpp
    include/Container.hpp
    include/Detail/Meta.hpp
    include/Vector2.hpp
    include/Quadtree.hpp
)
