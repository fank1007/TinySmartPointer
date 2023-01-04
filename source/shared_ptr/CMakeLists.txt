file(GLOB head ./*.cpp)

file(GLOB scr ./*.h)

add_executable(shared_ptr ${scr} ${head})