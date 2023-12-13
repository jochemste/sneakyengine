set(LIBNAME logger)

set(LOGGING_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")

set(SRCS
  logging.cpp
  )

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(${LIBNAME} PRIVATE SDL3::SDL3)

target_include_directories(
  ${LIBNAME}
  PUBLIC
  logger.hpp
  )
