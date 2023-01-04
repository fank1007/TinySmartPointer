file(GLOB head ./*.cpp)

file(GLOB scr ./*.h)

add_executable(unique_ptr ${scr} ${head})