find_package(SDL3 QUIET)
if(SDL3_FOUND)
  message(STATUS "Including SDL3 with find_package")
endif()

if(NOT SDL3_FOUND AND EXISTS "${CMAKE_CURRENT_LIST_DIR}/SDL/CMakeLists.txt")
  add_subdirectory(SDL)
  message(STATUS "Including SDL3 with add_subdirectory")
  set(SDL3_FOUND TRUE)
endif()

if(NOT SDL3_FOUND)
  include(FetchContent)
  set(SDL_SHARED TRUE CACHE BOOL "Build a SDL shared library if available")
  set(SDL_STATIC TRUE CACHE BOOL "Build a SDL static library if available")

  FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG main
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    )
  message(STATUS "Including SDL3 with FetchContent")
  FetchContent_MakeAvailable(SDL)
  set_property(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/_deps/sdl-src" PROPERTY EXCLUDE_FROM_ALL TRUE)
endif()

# Use this in the target executables/libraries
#target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
