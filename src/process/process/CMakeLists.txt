set(LIBNAME process)

# set externally used variables for header inclusion and lib linking
set(PROCESS_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
set(PROCESS_LIB ${LIBNAME} CACHE INTERNAL "")

# set source files
set(SRCS
  process.cpp
  processmanager_fact_impl.cpp
  processmanager_impl.cpp
  )

# include subdirectories
add_subdirectory(scheduler)
add_subdirectory(threadpool)

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
