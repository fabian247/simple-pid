#include "catch.hpp"

#include "../src/simple-pid.h"

TEST_CASE( "Simple PID function", "[simple-pid]" ) {
    REQUIRE( simplePid(1) == 1 );
}
