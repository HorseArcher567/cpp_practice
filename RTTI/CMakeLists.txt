add_executable(rtti
        rtti_unittest.cpp)

target_link_libraries(rtti GTest::gtest_main)
target_compile_options(rtti PRIVATE -g)

include(GoogleTest)
gtest_discover_tests(rtti)
