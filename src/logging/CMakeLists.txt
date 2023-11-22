set(LIBNAME logger)

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
