set(LIBNAME process)

# set externally used variables for header inclusion and lib linking
set(PROCESS_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "process include directory")
set(PROCESS_LIB ${LIBNAME} CACHE INTERNAL "process library name for linking")

# set source files
set(SRCS
  process.cpp
  )

# Set lib path for implementation submodules
set(PROCESS_IMPL_LIB_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/libs
  CACHE INTERNAL
  "process libraries path for implementations")
# include subdirectories
add_subdirectory(impl)

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(${LIBNAME}
  PRIVATE
  ${LINK_FOR_ALL}
  ${PROCESS_IMPL_LIB}
  )

target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${INCLUDE_FOR_ALL}
  ${PROCESS_INCLUDE}
  ${PROCESS_IMPL_INCLUDE}
  )
