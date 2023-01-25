add_executable(smart_pointer test.cpp)

target_link_libraries(smart_pointer gtest_main)

add_test(NAME SmartPointer COMMAND smart_pointer)

