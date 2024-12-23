# CMake minimum version requirement
cmake_minimum_required(VERSION 3.31.1)

# Project name
project(FunctionManager)

# 设置 C 标准版本
set(CMAKE_C_STANDARD 99)

# 添加源文件和头文件
set(SOURCES
    main.c
    test.c
)

set(HEADERS
    test.h
)

# 指定生成的可执行文件名称
add_executable(FunctionManager ${SOURCES} ${HEADERS})

# 包含头文件目录
target_include_directories(FunctionManager PRIVATE ${CMAKE_SOURCE_DIR})
