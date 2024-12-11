cmake_minimum_required(VERSION 3.29)
project(warShips)

set(CMAKE_CXX_STANDARD 20)

add_executable(warShips main.cpp
        game.cpp
        game.h
        oceanGrid.cpp
        oceanGrid.h
        targetGrid.cpp
        targetGrid.h
        ships.cpp
        ships.h
)
