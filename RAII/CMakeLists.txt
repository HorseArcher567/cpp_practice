add_executable(raii
        raii_unittest.cpp)

target_link_libraries(raii GTest::gtest_main)
target_compile_options(raii PRIVATE -g)

include(GoogleTest)
gtest_discover_tests(raii)