set(SRCS main.cpp engine.cpp colour.cpp coordinates.cpp shape.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${${PROJECTNAME}_SOURCE_DIR}/bin)
add_executable(${PROJECTNAME} ${SRCS})

# For finding our SDL2 package!
INCLUDE(FindPkgConfig)

# Searching SDL2 package.
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

# Including our external library's directory for header files!
message("Including ${SDL2_INCLUDE_DIRS}")
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

# Linking SDL2 library with our project.
message("Linking libraries ${SDL2_LIBRARIES}")
target_link_libraries(${PROJECTNAME} ${SDL2_LIBRARIES})
