cmake_minimum_required(VERSION 3.5)

project(simple-pid)

set(CMAKE_CXX_STANDARD 17)

add_library(simple-pid src/simple-pid.cpp)

add_executable(unit_tests test/simple-pid.unit-tests.cpp test/tests-main.cpp)

target_link_libraries(unit_tests simple-pid)

set_target_properties(unit_tests PROPERTIES
	COMPILE_FLAGS "-Wall -Wextra -Wpedantic -Werror"
)

add_custom_target(test DEPENDS unit_tests COMMAND unit_tests)
