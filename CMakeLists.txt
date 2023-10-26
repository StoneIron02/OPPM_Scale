cmake_minimum_required(VERSION 3.22)
project(OPPM_Scale)

set(CMAKE_CXX_STANDARD 17)

add_executable(OPPM_Scale
        OST.h
        Lmax_Lmin.h
        OPPM_Original.h
        OPPM_Scale.h
        main.cpp
        )
