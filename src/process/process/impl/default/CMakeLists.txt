set(LIBNAME process_default)

# set externally used variables for header inclusion and lib linking
set(PROCESS_IMPL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "process include directory")
set(PROCESS_IMPL_LIB ${LIBNAME} CACHE INTERNAL "process library name for linking")

# set source files
set(SRCS
  processmanager_fact_impl.cpp
  processmanager_impl.cpp
  )

# include subdirectories and set binary path to unique value (a Cmake
# thing it likes to complain about)
add_subdirectory(
  ${PROCESS_IMPL_LIB_PATH}/scheduler
  ${CMAKE_CURRENT_BINARY_DIR}/scheduler)
add_subdirectory(
  ${PROCESS_IMPL_LIB_PATH}/threadpool
  ${CMAKE_CURRENT_BINARY_DIR}/threadpool)

add_library(
  ${LIBNAME}
  ${SRCS}
  )

target_link_libraries(${LIBNAME}
  PRIVATE
  SDL3::SDL3
  ${LINK_FOR_ALL}
  ${SCHEDULER_LIB}
  ${THREADPOOL_LIB}
  )

target_include_directories(
  ${LIBNAME}
  PRIVATE
  ${INCLUDE_FOR_ALL}
  ${SCHEDULER_INCLUDE}
  ${THREADPOOL_INCLUDE}
  ${PROCESS_INCLUDE}
  )
