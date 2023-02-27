cmake_minimum_required(VERSION 3.10)


# set the project name
project(EXAMPLE_ONE_BASIC_SYNC_TOOL VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMDTL_INCLUDE_DIR "../../include")

include_directories(${CMDTL_INCLUDE_DIR})

add_executable(EXAMPLE_ONE_BASIC_SYNC_TOOL main.cpp)
