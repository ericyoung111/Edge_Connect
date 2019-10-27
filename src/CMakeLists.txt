cmake_minimum_required(VERSION 3.5)

project(Edge_Connect)

set(WSMP_SRC
    ./v2x/v2x_wsmp.c)

set(CMAKE_C_FLAGS "-Wall -Werror")

include_directories(
    ./v2x/)

add_library(v2x_wsmp ${WSMP_SRC})