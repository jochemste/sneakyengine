set(LIBNAME logger_sdl3)

set(LOGGING_IMPL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "logging include directory")
set(LOGGING_IMPL_LIB SDL3::SDL3 CACHE INTERNAL "logging libname for linking")
