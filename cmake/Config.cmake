# Build configuration

set(SE_CONF_STR "++ CONFIG ++: ")
message(${PROJECTNAME} " configuration:")

# Temporary definition of debug build, until available as a CLI option
set(CMAKE_BUILD_TYPE Debug)
add_definitions(-DDEBUG)
message(${SE_CONF_STR} "Build type -> " ${CMAKE_BUILD_TYPE})

option(SE_INCLUDE_TESTS "Include tests in build" ON)
message(${SE_CONF_STR} "Include tests -> " ${SE_INCLUDE_TESTS})

set(SE_ENGINE_BACKEND "SDL3")
message(${SE_CONF_STR} "Engine backend -> " ${SE_ENGINE_BACKEND})
