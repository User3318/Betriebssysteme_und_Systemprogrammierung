cmake_minimum_required(VERSION 3.10)
project(ErzeugerVerbraucherMutex)

set(CMAKE_CXX_FLAGS "-std=c++17 -pthread  ${CMAKE_CXX_FLAGS}")

include_directories(
        include
)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Schreiber.cpp
        src/Leser.cpp
        )