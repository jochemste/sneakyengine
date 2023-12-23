set(LIBNAME process)

set(PROCESS_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
set(PROCESS_LIB ${LIBNAME} CACHE INTERNAL "")

# include subdirectories
add_subdirectory(scheduler)

set(SRCS
  process.cpp
  )

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(${LIBNAME}
  PRIVATE
  SDL3::SDL3
  ${LINK_FOR_ALL}
  ${SCHEDULER_LIB}
  )
target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${INCLUDE_FOR_ALL}
  ${SCHEDULER_INCLUDE}
  )