set(LIBNAME process_impl)

set(PROCESS_IMPL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
set(PROCESS_IMPL_LIB ${LIBNAME} CACHE INTERNAL "")

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
