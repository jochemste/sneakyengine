set(LIBNAME display)

set(DISPLAY_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
set(DISPLAY_LIB ${LIBNAME} CACHE INTERNAL "")

set(SRCS
  display_sdl_impl.cpp
  display.cpp
  )

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(${LIBNAME} PRIVATE SDL3::SDL3 ${LOGGING_LIB})
target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${LOGGING_INCLUDE}
  ${UTILS_INCLUDE}
  )
