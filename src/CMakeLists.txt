set(SRCS main.cpp engine.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${${PROJECTNAME}_SOURCE_DIR}/bin)

add_executable(${PROJECTNAME} ${SRCS})
add_library(${PROJECTNAME}_lib STATIC ${SRCS})

# For finding our SDL2 package!
#INCLUDE(FindPkgConfig)

# Searching SDL2 package.
#PKG_SEARCH_MODULE(SDL3 REQUIRED sdl3)

# Including our external library's directory for header files!
message("Including ${SDL3_INCLUDE_DIRS}")
#INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

# Linking SDL2 library with our project.
message("Linking libraries ${SDL3_LIBRARIES}")
#target_link_libraries(${PROJECTNAME} ${SDL3_LIBRARIES})
