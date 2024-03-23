set(SRCS main.cpp engine.cpp)

# include logging for all
add_subdirectory(logging)
set(INCLUDE_FOR_ALL ${LOGGING_INCLUDE})
set(LINK_FOR_ALL ${LOGGING_LIB})

# Follow order of dependencies
add_subdirectory(utils)
add_subdirectory(common)
add_subdirectory(process)

add_subdirectory(display)
add_subdirectory(input)


add_executable(${PROJECTNAME} ${SRCS})

target_link_libraries(${PROJECTNAME}
  PRIVATE
  ${LINK_FOR_ALL}
  ${PROCESS_LIB}
  ${DISPLAY_PROC_LIB}
  ${EVENT_PROC_LIB}
  )
target_include_directories(
  ${PROJECTNAME}
  PRIVATE
  ${INCLUDE_FOR_ALL}
  ${PROCESS_INCLUDE}
  ${DISPLAY_PROC_INCLUDE}
  ${EVENT_PROC_INCLUDE}
  )

