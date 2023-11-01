# function to add tests for a library, used to test small modules, built as libraries
function(add_test_for_library test_target test_name)
  # Define test executable
  add_executable(
    ${test_name}
    ${test_name}.cpp
    )

  # Link test executable to the library
  target_link_libraries(
    ${test_name}
    ${test_target}
    GTest::gtest_main)

  gtest_discover_tests(${test_name})

  # Add memory test
  add_test(
    NAME ${test_name}_memory
    COMMAND /usr/bin/valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all ${CMAKE_BINARY_DIR}/test/${test_name})
endfunction()
