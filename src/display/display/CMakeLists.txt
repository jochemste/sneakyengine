set(LIBNAME display)

set(DISPLAY_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "display include directory")
set(DISPLAY_LIB ${LIBNAME} CACHE INTERNAL "display library name for linking")

set(SRCS
  display.cpp
  )

# sets DISPLAY_IMPL_INCLUDE and DISPLAY_IMPL_LIB
add_subdirectory(impl)

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(${LIBNAME}
  PRIVATE
  ${LINK_FOR_ALL}
  ${DISPLAY_IMPL_LIB}
  )
target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${INCLUDE_FOR_ALL}
  ${UTILS_INCLUDE}
  ${DISPLAY_INCLUDE}
  ${DISPLAY_IMPL_INCLUDE}
  )
