cmake_minimum_required(VERSION 3.8)
project(EksamensInnlevering)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES Main.c Main.h NodeMethods.c NodeMethods.h Utils.c Utils.h)
add_executable(EksamensInnlevering ${SOURCE_FILES})