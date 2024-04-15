set(LIBNAME subscr_admin)

set(SUBSCR_ADMIN_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "subscr_admin include path")
set(SUBSCR_ADMIN_LIB ${LIBNAME} CACHE INTERNAL "subscr_admin libname for linking")

set(SRCS
  subscr_admin.cpp
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
  ${UTILS_INCLUDE}
  ${MOD_SERVER_INCLUDE}
  ${SUBSCR_ADMIN_INCLUDE}
  )
