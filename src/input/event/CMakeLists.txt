set(LIBNAME event)

set(EVENT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "event include directory")
set(EVENT_LIB ${LIBNAME} CACHE INTERNAL "event library name for linking")

set(SRCS
  eventhandler_impl.cpp
  event.cpp
  )

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(${LIBNAME}
  PRIVATE
  ${LINK_FOR_ALL}
  ${INPUT_LIB}
  )
target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${INCLUDE_FOR_ALL}
  ${INPUT_INCLUDE}
  )
