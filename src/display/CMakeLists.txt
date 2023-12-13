set(LIBNAME display)

set(DISPLAY_DIRS ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")

set(SRCS
  display_sdl_impl.cpp
  display.cpp
  )

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(${LIBNAME} PRIVATE SDL3::SDL3 logger)
target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${LOGGING_INCLUDE}
  )
