set(SRCS main.cpp engine.cpp)

# include modules
add_subdirectory(logging)
add_subdirectory(utils)
add_subdirectory(display)
add_subdirectory(process)


add_executable(${PROJECTNAME} ${SRCS})

target_link_libraries(${PROJECTNAME}
  PRIVATE
  ${LOGGING_LIB}
  ${DISPLAY_LIB}
  ${PROCESS_LIB}
  )
target_include_directories(
  ${PROJECTNAME}
  PRIVATE
  ${LOGGING_INCLUDE}
  ${DISPLAY_INCLUDE}
  ${PROCESS_INCLUDE}
  )

