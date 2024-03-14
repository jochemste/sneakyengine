set(LIBNAME event_process)

set(EVENT_PROC_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH
  "event process include directory")
set(EVENT_PROC_LIB ${LIBNAME} CACHE INTERNAL "event process libname for linking")

set(SRCS
  event_proc.cpp
  )

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(${LIBNAME}
  PRIVATE
  ${LINK_FOR_ALL}
  ${EVENT_LIB}
  )
target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${INCLUDE_FOR_ALL}
  ${PROCESS_INCLUDE}
  ${EVENT_INCLUDE}
  )
