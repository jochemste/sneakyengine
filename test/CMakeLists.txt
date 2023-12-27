include(TestFunctions)

enable_testing()

set(SRCS
  test_engine.cpp
  test_scheduler.cpp
  )

add_executable(
  test_engine
  ${SRCS}
  )

target_link_libraries(
  test_engine
  GTest::gtest_main
  ${SCHEDULER_LIB}
  )

target_include_directories(
  test_engine
  PRIVATE
  ${SCHEDULER_INCLUDE}
  )

include(GoogleTest)
gtest_discover_tests(test_engine)
