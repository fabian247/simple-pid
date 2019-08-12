#include "catch.hpp"

#include "../src/simple-pid.h"

SCENARIO("PID functionality", "[simple-pid]") {
	GIVEN("A fully populated PID function") {
		simple_pid::Simple_Pid pid = simple_pid::Simple_Pid(100, 1, 1, 0.1, 0);

		GIVEN("A constant input matching the target value") {
			REQUIRE(pid.calc_output(100, 100) == 100);
			REQUIRE(pid.calc_output(100, 200) == 100);
			REQUIRE(pid.calc_output(100, 300) == 100);
			REQUIRE(pid.calc_output(100, 400) == 100);

			WHEN("the input increases") {
				THEN("the output should decrease") {
					double output1 = pid.calc_output(150, 500);
					double output2 = pid.calc_output(200, 1000);
					REQUIRE(output2 < output1);
				}
			}

			WHEN("the input decreases") {
				THEN("the output should increase") {				
					double output1 = pid.calc_output(80, 1500);
					double output2 = pid.calc_output(50, 2000);
					REQUIRE(output2 > output1);
				}
			}	
		}
	}

	GIVEN("A P function") {
		simple_pid::Simple_Pid p_func = simple_pid::Simple_Pid(100, 1, 0, 0, 0);

		GIVEN("A constant input matching the target value") {
			REQUIRE(p_func.calc_output(100, 100) == 100);
			REQUIRE(p_func.calc_output(100, 200) == 100);
			REQUIRE(p_func.calc_output(100, 300) == 100);
			REQUIRE(p_func.calc_output(100, 400) == 100);

			WHEN("the input increases") {
				THEN("the output should decrease") {
					double output1 = p_func.calc_output(150, 500);
					double output2 = p_func.calc_output(200, 1000);
					REQUIRE(output2 < output1);
				}
			}

			WHEN("the input decreases") {
				THEN("the output should increase") {				
					double output1 = p_func.calc_output(80, 1500);
					double output2 = p_func.calc_output(50, 2000);
					REQUIRE(output2 > output1);
				}
			}	
		}
	}

	GIVEN("An I function") {
		simple_pid::Simple_Pid i_func = simple_pid::Simple_Pid(100, 0, 1, 0, 0);

		GIVEN("A constant input matching the target value") {
			REQUIRE(i_func.calc_output(100, 100) == 100);
			REQUIRE(i_func.calc_output(100, 200) == 100);
			REQUIRE(i_func.calc_output(100, 300) == 100);
			REQUIRE(i_func.calc_output(100, 400) == 100);

			WHEN("the input increases") {
				THEN("the output should decrease") {
					double output1 = i_func.calc_output(150, 500);
					double output2 = i_func.calc_output(200, 600);
					REQUIRE(output2 < output1);
				}
			}
			
			WHEN("the input decreases") {
				THEN("the output should increase") {				
					double output1 = i_func.calc_output(80, 1500);
					double output2 = i_func.calc_output(50, 2000);
					REQUIRE(output2 > output1);
				}
			}	
		}
	}
		
	GIVEN("An I function with limited min output") {
		simple_pid::Simple_Pid i_func = simple_pid::Simple_Pid(100, 0, 1, 0, 0);
		i_func.set_min_output(-10);

		GIVEN("A constant input matching the target value") {
			REQUIRE(i_func.calc_output(100, 100) == 100);
			REQUIRE(i_func.calc_output(100, 200) == 100);
			REQUIRE(i_func.calc_output(100, 300) == 100);
			REQUIRE(i_func.calc_output(100, 400) == 100);

			WHEN("an increasing input would result in an output below min output") {
				THEN("the output shold not decrease") {
					double output1 = i_func.calc_output(101, 500);
					double output2 = i_func.calc_output(200, 600);
					REQUIRE(output1 < 100);
					REQUIRE(output2 == output1);
				}
			}
		}
	}	
	
	GIVEN("An I function with limited max output") {
		simple_pid::Simple_Pid i_func = simple_pid::Simple_Pid(100, 0, 1, 0, 0);
		i_func.set_max_output(10);

		GIVEN("A constant input matching the target value") {
			REQUIRE(i_func.calc_output(100, 100) == 100);
			REQUIRE(i_func.calc_output(100, 200) == 100);
			REQUIRE(i_func.calc_output(100, 300) == 100);
			REQUIRE(i_func.calc_output(100, 400) == 100);

			WHEN("an decreasing input sould result in an output above max output") {
				THEN("the output should  not increase") {				
					double output1 = i_func.calc_output(99, 500);
					double output2 = i_func.calc_output(0, 600);
					REQUIRE(output1 > 100);
					REQUIRE(output2 == output1);
				}
			}	
		}
	}

	GIVEN("A D function") {
		simple_pid::Simple_Pid d_func = simple_pid::Simple_Pid(100, 0, 0, 1, 0);

		GIVEN("A constant input matching the target value") {
			REQUIRE(d_func.calc_output(100, 100) == 100);
			REQUIRE(d_func.calc_output(100, 200) == 100);
			REQUIRE(d_func.calc_output(100, 300) == 100);
			REQUIRE(d_func.calc_output(100, 400) == 100);

			WHEN("the input increases linear") {
				THEN("the output should be constant") {
					double output1 = d_func.calc_output(150, 500);
					double output2 = d_func.calc_output(200, 600);
					REQUIRE(output2 == output1);
				}
			}

			WHEN("the input increases non-linear") {
				THEN("the output should decrease") {
					double output1 = d_func.calc_output(120, 500);
					double output2 = d_func.calc_output(200, 600);
					REQUIRE(output2 < output1);
				}
			}		
		}
	}
}

