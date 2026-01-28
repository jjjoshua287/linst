cmake_minimum_required(VERSION 3.10)

project(Linst VERSION 0.1.0 DESCRIPTION "Multi-distro software automation tool")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(linst
    src/main.cpp
    src/DistroDetector.cpp
    src/PackageResolver.cpp
    src/DistroDetector.h
    src/PackageData.h
)

target_include_directories(linst PRIVATE
    src
)