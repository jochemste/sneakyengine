set(LIBNAME input)

set(INPUT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "input include directory")
set(INPUT_LIB ${LIBNAME} CACHE INTERNAL "input library name for linking")

set(SRCS
  input.cpp
  )

# Add implementations directory
add_subdirectory(impl)

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(${LIBNAME}
  PRIVATE
  ${LINK_FOR_ALL}
  ${INPUTPOLLERSDL_LIB}
  )
target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${INCLUDE_FOR_ALL}
  ${UTILS_INCLUDE}
  ${INPUT_INCLUDE}
  ${INPUTPOLLERSDL_INCLUDE}
  )
