include(TestFunctions)

enable_testing()

add_executable(
  test_engine
  test_engine.cpp
  )

target_link_libraries(
  test_engine
  GTest::gtest_main
  )

include(GoogleTest)
gtest_discover_tests(test_engine)
