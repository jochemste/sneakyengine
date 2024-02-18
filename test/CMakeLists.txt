include(TestFunctions)

enable_testing()

set(SRCS
  test_engine.cpp
  process/test_scheduler.cpp
  process/test_processmanager.cpp
  process/test_threadpool.cpp
  )

add_executable(
  test_engine
  ${SRCS}
  )

target_link_libraries(
  test_engine
  GTest::gtest_main
  GTest::gmock_main
  ${LOGGING_LIB}
  ${SCHEDULER_LIB}
  ${PROCESS_LIB}
  ${THREADPOOL_LIB}
  )

target_include_directories(
  test_engine
  PRIVATE
  mocks
  ${LOGGING_INCLUDE}
  ${SCHEDULER_INCLUDE}
  ${PROCESS_INCLUDE}
  ${THREADPOOL_INCLUDE}
  )

include(GoogleTest)
gtest_discover_tests(test_engine)
