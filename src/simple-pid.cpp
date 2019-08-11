#include "simple-pid.h"

#include <iostream>

simple_pid::Simple_Pid::Simple_Pid(double target_value, double p, double i, double d, double initial_timestamp) 
{
	_previous_error = 0;
	_integral = 0;
	_previous_timestamp = initial_timestamp;
	_target_value = target_value;
	_p = p;
	_i = i;
	_d = d;
}

double simple_pid::Simple_Pid::calc_output(double input, double timestamp_in_millis) 
{
	double error = _target_value - input;
	double delta_time = timestamp_in_millis - _previous_timestamp;

	_integral += error * delta_time;
	double derivative = (error - _previous_error) / delta_time;

	double output = _target_value * (1 + (_p * error + _i * _integral + _d * derivative));
	
	_previous_error = error;
	_previous_timestamp = timestamp_in_millis;

	return output;
}
