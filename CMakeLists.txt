cmake_minimum_required(VERSION 3.8)
project(EksamensInnlevering)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES KeyValueDB.c headerfiles/KeyValueDB.h sourcefiles/FileReading.c headerfiles/FileReading.h sourcefiles/FileWriting.c headerfiles/FileWriting.h sourcefiles/Validation.c headerfiles/Validation.h)
add_executable(EksamensInnlevering ${SOURCE_FILES})