set(LIBNAME process)

# include subdirectories
add_subdirectory(scheduler)

set(PROCESS_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
set(PROCESS_LIB ${LIBNAME} CACHE INTERNAL "")

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
  )
target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${INCLUDE_FOR_ALL}
  )
