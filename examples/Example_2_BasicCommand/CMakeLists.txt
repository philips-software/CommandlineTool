cmake_minimum_required(VERSION 3.10)


# set the project name
project(EXAMPLE_TWO_BASIC_COMMAND VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMDTL_INCLUDE_DIR "../../include")
set(EXAMPLE_TWO_INCLUDE  "")
set(LIBS_INCLUDE "../../libs/")

include_directories(${CMDTL_INCLUDE_DIR})
include_directories(${LIBS_INCLUDE})
include_directories(${EXAMPLE_TWO_INCLUDE})

add_executable(EXAMPLE_TWO_BASIC_COMMAND main.cpp)
