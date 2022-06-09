cmake_minimum_required (VERSION 3.23)
set(CMAKE_BUILD_TYPE Debug)

set(PROJECTNAME "sneakyengine")

set(CMAKE_CXX_STANDARD 20)

# Below line is for using C++20 standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

project (${PROJECTNAME})

message("Configuring build files for ${PROJECTNAME}")

find_package(SDL2 REQUIRED)
if (NOT SDL2_FOUND)
  message(FATAL_ERROR "SDL2 required but not found")
endif()

# Source code
add_subdirectory(src)
# Testing directories
add_subdirectory(test)
add_subdirectory(lib/googletest)
# Doxygen docs
option(BUILD_WITH_DOCS "Generate Docs" ON)
#if(TASKSCH_BUILD_WITH_DOCS)
  add_subdirectory(doc)
#endif()

install(TARGETS ${PROJECTNAME} DESTINATION ${${PROJECTNAME}_SOURCE_DIR}/bin)
