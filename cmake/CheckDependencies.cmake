message(STATUS "Checking dependencies")

find_package( Doxygen )
if(DOXYGEN_FOUND)
  message(STATUS "Doxygen found: ${DOXYGEN_EXECUTABLE} v${DOXYGEN_VERSION}")
else()
  message(STATUS "Doxygen was not found, disabling doxygen build")
  set(BUILD_WITH_DOCS OFF)
endif()
