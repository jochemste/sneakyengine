cmake_minimum_required (VERSION 3.25)

# Temporary definition of debug build, until available as a CLI option
set(CMAKE_BUILD_TYPE Debug)
add_definitions(-DDEBUG)

set(PROJECTNAME "sneakyengine")
project (${PROJECTNAME} VERSION "0.0.1" LANGUAGES C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

message("Configuring build files for ${PROJECTNAME}")

# Include cmake scripts
include(CheckDependencies)
include(BuildRules)
include(Options)
include(GetSDL)
include(GetGTest)

# Source code
add_subdirectory(src)

# Testing directories
add_subdirectory(test)

# Doxygen docs
if(BUILD_WITH_DOCS)
  add_subdirectory(doc)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

install(TARGETS ${PROJECTNAME} DESTINATION ${${PROJECTNAME}_SOURCE_DIR}/bin)
