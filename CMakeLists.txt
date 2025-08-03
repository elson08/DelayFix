cmake_minimum_required(VERSION 3.20)
project(DelayFix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(DelayFix SHARED
        main.cpp
        util/Logger.h
        util/MemoryUtil.h
)

add_subdirectory(include/libhat)
target_link_libraries(DelayFix PRIVATE libhat)
target_include_directories(DelayFix PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/libhat/include)

set_property(TARGET DelayFix libhat PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
