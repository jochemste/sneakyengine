set(EXEC_TST ${PROJECTNAME}_tst)
set(TST_SRCS main.cpp coordinates_tst.hpp)

project(${EXEC_TST})

add_executable(${EXEC_TST} ${TST_SRCS})
add_test(NAME ${EXEC_TST} COMMAND ${EXEC_TST})

target_link_libraries(${EXEC_TST} PUBLIC ${PROJECTNAME}_lib gtest ${SDL2_LIBRARIES})
