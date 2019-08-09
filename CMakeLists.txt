cmake_minimum_required(VERSION 3.5)

project(simple-pid)

set(CMAKE_CXX_STANDARD 17)

add_executable(simple-pid test/simple-pid.unit-tests.cpp test/tests-main.cpp src/simple-pid.cpp)

set_target_properties(simple-pid PROPERTIES
	COMPILE_FLAGS "-Wall -Wextra -Wpedantic -Werror"
)

# Run the tests on every build
add_custom_target(test_simple-pid ALL DEPENDS simple-pid COMMAND simple-pid)
