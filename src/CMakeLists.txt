set(SRCS main.cpp engine.cpp)

# include modules
add_subdirectory(logging)
add_subdirectory(display)

add_executable(${PROJECTNAME} ${SRCS})

target_link_libraries(${PROJECTNAME}
  PRIVATE
  logger
  display
  )
target_include_directories(
  ${PROJECTNAME}
  PRIVATE
  ${LOGGING_INCLUDE}
  ${DISPLAY_DIRS}
  )

