add_executable(friends
        friends_unittest.cpp)

target_link_libraries(friends GTest::gtest_main)
target_compile_options(friends PRIVATE -g)

include(GoogleTest)
gtest_discover_tests(friends)