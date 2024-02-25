set(LIBNAME display_process)

set(DISPLAY_PROC_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH
  "display process include directory")
set(DISPLAY_PROC_LIB ${LIBNAME} CACHE INTERNAL "display process libname for linking")

set(SRCS
  display_proc_impl.cpp
  )

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(${LIBNAME}
  PRIVATE
  ${LINK_FOR_ALL}
  ${PROCESS_LIB}
  ${DISPLAY_LIB}
  )
target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${INCLUDE_FOR_ALL}
  ${PROCESS_INCLUDE}
  ${DISPLAY_INCLUDE}
  )
