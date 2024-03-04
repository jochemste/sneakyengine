set(LIBNAME inputpollerSDL)

set(INPUTPOLLERSDL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "inputSDL include directory")
set(INPUTPOLLERSDL_LIB ${LIBNAME} CACHE INTERNAL "inputSDL library name for linking")

set(SRCS
  inputpoller_sdl_impl.cpp
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
  PUBLIC
  ${INCLUDE_FOR_ALL}
  ${INPUTPOLLERSDL_INCLUDE}
  ${INPUT_INCLUDE}
  )
