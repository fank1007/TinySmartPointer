cmake_minimum_required(VERSION 3.5)

project(TinySmartPointer)

include_directories(googletest/googletest/include)

enable_testing()

include_directories(source)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(googletest)

add_subdirectory(test)