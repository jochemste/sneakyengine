set(SRCS main.cpp engine.cpp)

# include logging for all
add_subdirectory(logging)
set(INCLUDE_FOR_ALL ${LOGGING_INCLUDE})
set(LINK_FOR_ALL ${LOGGING_LIB})

add_subdirectory(utils)
add_subdirectory(display)
add_subdirectory(process)


add_executable(${PROJECTNAME} ${SRCS})

target_link_libraries(${PROJECTNAME}
  PRIVATE
  ${LINK_FOR_ALL}
  ${DISPLAY_LIB}
  ${PROCESS_LIB}
  )
target_include_directories(
  ${PROJECTNAME}
  PRIVATE
  ${INCLUDE_FOR_ALL}
  ${DISPLAY_INCLUDE}
  ${PROCESS_INCLUDE}
  )

