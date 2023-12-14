set(LIBNAME process)

set(PROCESS_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
set(PROCESS_LIB ${LIBNAME} CACHE INTERNAL "")

set(SRCS
  process.cpp
  )

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(${LIBNAME} PRIVATE SDL3::SDL3 ${LOGGING_LIB})
target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${LOGGING_INCLUDE}
  )
