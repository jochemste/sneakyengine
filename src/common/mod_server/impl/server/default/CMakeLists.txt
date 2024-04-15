set(LIBNAME server)

set(SERVER_INCLUDE
  ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "server include directory")
set(SERVER_LIB
  ${LIBNAME} CACHE INTERNAL "server library name for linking")

set(SRCS
  server_impl.cpp
  )

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(
  ${LIBNAME}
  PRIVATE
  ${LINK_FOR_ALL}
  )
target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${INCLUDE_FOR_ALL}
  ${UTILS_INCLUDE}
  ${MOD_SERVER_INCLUDE}
  )
