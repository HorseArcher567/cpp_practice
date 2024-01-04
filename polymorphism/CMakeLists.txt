add_executable(
        polymorphism
        polymorphism_unittest.cpp
)
target_link_libraries(
        polymorphism
        GTest::gtest_main
)
target_compile_options(polymorphism PRIVATE -g)

include(GoogleTest)
gtest_discover_tests(polymorphism)
