cmake_minimum_required(VERSION 3.22)
project(OPPM_Scale)

set(CMAKE_CXX_STANDARD 14)

add_executable(OPPM_Scale
        OST.h
        Lmax_Lmin.h
        OPPM_Original.h
        OPPM_Scale.h
        OPPM_Scale.cpp)
