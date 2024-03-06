cmake_minimum_required (VERSION 3.25)



set(PROJECTNAME "sneakyengine")
project (${PROJECTNAME} VERSION "0.0.1" LANGUAGES C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

message("Configuring build files for ${PROJECTNAME}")

# Include cmake scripts
include(Config) # Needs to be included first, holds build configuration
include(CheckDependencies)
include(BuildRules)
include(Options)

# More cmake scripts, depending on the previous ones
if (SE_ENGINE_BACKEND STREQUAL "SDL3")
  include(GetSDL3)
  set(SE_LINK_BACKEND SDL3::SDL3)
endif()

# Source code
add_subdirectory(src)

# Testing directories
if (SE_INCLUDE_TESTS)
  include(GetGTest)
  add_subdirectory(test)
endif()

# Doxygen docs
if(BUILD_WITH_DOCS)
  add_subdirectory(doc)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${SE_LINK_BACKEND})

install(TARGETS ${PROJECTNAME} DESTINATION ${${PROJECTNAME}_SOURCE_DIR}/bin)
