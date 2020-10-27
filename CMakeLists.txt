cmake_minimum_required(VERSION 3.17)
project(ConcuSat)

include_directories(config)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        concuSat
        config/Config.cpp
        config/Config.h
        observatorio/Observatorio.cpp
        observatorio/Observatorio.h
        main.cpp

)