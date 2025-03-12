cmake_minimum_required(VERSION 3.10)
project(BackupSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(libzip REQUIRED)

add_executable(BackupSystem
    src/main.cpp
)

target_link_libraries(BackupSystem libzip::zip)

if(UNIX)
    target_link_libraries(BackupSystem stdc++fs)
endif()
