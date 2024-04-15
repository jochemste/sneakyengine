set(LIBNAME mod_server)

set(MOD_SERVER_INCLUDE
  ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "mod_server include directory")
set(MOD_SERVER_LIB
  ${LIBNAME} CACHE INTERNAL "mod_server library name for linking")

set(SRCS
  module_server.cpp
  )

# Add library directories
add_subdirectory(libs/subscr_admin)
# Add implementation directory
add_subdirectory(impl)

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(
  ${LIBNAME}
  PRIVATE
  ${LINK_FOR_ALL}
  ${MESSAGE_LIB}
  )
target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${INCLUDE_FOR_ALL}
  ${UTILS_INCLUDE}
  ${MOD_SERVER_INCLUDE}
  ${MESSAGE_INCLUDE}
  )
