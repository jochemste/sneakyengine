set(LIBNAME scheduler)

set(SCHEDULER_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "scheduler include directory")
set(SCHEDULER_LIB ${LIBNAME} CACHE INTERNAL "scheduler libname for linking")

set(SRCS
  scheduler.cpp
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
