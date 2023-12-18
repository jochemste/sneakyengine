set(LIBNAME scheduler)

set(SCHEDULER_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
set(SCHEDULER_LIB ${LIBNAME} CACHE INTERNAL "")

set(SRCS
  scheduler.cpp
  scheduler_fact_impl.cpp
  scheduler_fifo.cpp
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
  )
