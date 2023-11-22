set(SRCS main.cpp engine.cpp)

# include modules
add_subdirectory(logging)

add_executable(${PROJECTNAME} ${SRCS})

target_link_libraries(${PROJECTNAME} PRIVATE logger)
target_include_directories(${PROJECTNAME} PRIVATE logging)
