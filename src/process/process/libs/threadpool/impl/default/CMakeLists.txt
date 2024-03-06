set(LIBNAME threadpool_default)

set(THREADPOOL_IMPL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "threadpool include path")
set(THREADPOOL_IMPL_LIB ${LIBNAME} CACHE INTERNAL "threadpool libname for linking")

set(SRCS
  threadpool_impl.cpp
  )

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(${LIBNAME}
  PRIVATE
  ${LINK_FOR_ALL}
  )

target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${INCLUDE_FOR_ALL}
  ${THREADPOOL_INCLUDE}
  ${PROCESS_INCLUDE}
  )
