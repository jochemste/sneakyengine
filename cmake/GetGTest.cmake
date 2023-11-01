
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
  )
message(STATUS "Including GoogleTest with FetchContent")
FetchContent_MakeAvailable(googletest)
