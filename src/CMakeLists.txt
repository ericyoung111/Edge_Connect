cmake_minimum_required(VERSION 3.5)

project(Edge_Connect)

set(WSMP_SRC
    ./v2x/network_codecs/v2x_wsmp.c
    ./v2x/network_codecs/v2x_wsa.cc
    ./v2x/network_codecs/v2x_codec_util.c)

# use clang as compiler
set(CMAKE_C_COMPILER "clang")

set(CMAKE_C_FLAGS "-Wall -Werror -Wextra -Wno-unused-parameter")

include_directories(
    ./v2x/
    ./v2x/network_codecs/)

add_library(v2x_wsmp ${WSMP_SRC})