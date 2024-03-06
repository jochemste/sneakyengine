set(LIBNAME threadpool)

set(THREADPOOL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "threadpool include path")
set(THREADPOOL_LIB ${LIBNAME} CACHE INTERNAL "threadpool libname for linking")

set(SRCS
  threadpool.cpp
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
