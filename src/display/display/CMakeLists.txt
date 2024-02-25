set(LIBNAME display)

set(DISPLAY_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "display include directory")
set(DISPLAY_LIB ${LIBNAME} CACHE INTERNAL "display library name for linking")

set(SRCS
  display_sdl_impl.cpp
  display.cpp
  )

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(${LIBNAME}
  PRIVATE
  SDL3::SDL3
  ${LINK_FOR_ALL}
  )
target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${INCLUDE_FOR_ALL}
  ${UTILS_INCLUDE}
  )
