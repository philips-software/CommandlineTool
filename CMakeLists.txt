cmake_minimum_required(VERSION 3.10)

# set the project name
project(CMDTL VERSION 1.0)

# configure_file(*.hpp.in *.hpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMDTL_MAJOR_VERSION 1)
set(CMDTL_MINOR_VERSION 0)
set(CMDTL_PATCH_VERSION 0)
set(CMDTL_VERSION ${CMDTL_MAJOR_VERSION}.${CMDTL_MINOR_VERSION}.${CMDTL_PATCH_VERSION})
set(CMDTL_VERSION_STRING "${CMDTL_VERSION}")

file(GLOB INTERFACE
     "/*.hpp"
)

add_library(CMDTL INTERFACE)

target_include_directories(CMDTL
          INTERFACE "include\\"}
          )

#set_target_properties(CMDTL PROPERTIES LINKER_LANGUAGE CXX)

# target_link_library(another-users-target CMDTL)
