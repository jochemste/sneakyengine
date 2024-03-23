set(LIBNAME message)

set(MESSAGE_INCLUDE
  ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "message include directory")
set(MESSAGE_LIB
  ${LIBNAME} CACHE INTERNAL "message library name for linking")

set(SRCS
  message_impl.cpp
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
