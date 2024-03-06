set(LIBNAME display_sdl3)

set(DISPLAY_IMPL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "display include directory")
set(DISPLAY_IMPL_LIB ${LIBNAME} CACHE INTERNAL "display library name for linking")

set(SRCS
  display_sdl_impl.cpp
  )

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(${LIBNAME}
  PUBLIC
  SDL3::SDL3
  PRIVATE
  ${LINK_FOR_ALL}
  )
target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${INCLUDE_FOR_ALL}
  ${UTILS_INCLUDE}
  ${DISPLAY_INCLUDE}
  )
