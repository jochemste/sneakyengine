set(LIBNAME logger)

set(LOGGING_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "logging include directory")
set(LOGGING_LIB ${LIBNAME} CACHE INTERNAL "logging libname for linking")

set(SRCS
  logging.cpp
  )

add_subdirectory(impl)

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(
  ${LIBNAME}
  PRIVATE
  ${LOGGING_IMPL_LIB}
  )

target_include_directories(
  ${LIBNAME}
  PUBLIC
  ${LOGGING_IMPL_INCLUDE}
  ${LOGGING_INCLUDE}
  )
