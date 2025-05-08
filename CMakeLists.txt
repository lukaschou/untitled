cmake_minimum_required(VERSION 3.16)
project(Untitled C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

file(GLOB SOURCES "src/*.c" "game.c" "galaxy.c" "orders.c")

add_executable(untitled ${SOURCES})
