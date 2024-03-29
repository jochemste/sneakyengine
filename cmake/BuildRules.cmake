message(STATUS "Setting buildrules")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GCC builds
if(CMAKE_COMPILER_IS_GNUCXX)
  message("GCC compiler found.")
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "-g")
  endif()

  # warnings
  set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wno-sign-conversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function")

  # sanitize
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")

  # Below line is for using C++20 standard
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
else()
  message("WARNING: GCC not found, ${PROJECTNAME} build untested")
endif(CMAKE_COMPILER_IS_GNUCXX)
# End of GCC builds

message("Compiling with flags: ${CMAKE_CXX_FLAGS}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${${PROJECTNAME}_SOURCE_DIR}/bin)
