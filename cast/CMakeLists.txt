add_executable(
        cast
        cast_unittest.cpp
        data_def.h
)

target_link_libraries(
        cast
        GTest::gtest_main
)
target_compile_options(cast PRIVATE -g)

include(GoogleTest)
gtest_discover_tests(cast)