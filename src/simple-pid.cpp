#include "simple-pid.h"

#include <iostream>
#include <limits>

using namespace simple_pid;

Simple_Pid::Simple_Pid(double target_value, double p, double i, double d, double initial_timestamp) 
{
	_previous_error = 0;
	_integral = 0;
	_previous_timestamp = initial_timestamp;
	_target_value = target_value;
	_max_output = std::numeric_limits<double>::max() / 10;
	_min_output = std::numeric_limits<double>::lowest() / 10;
	_p = p;
	_i = i;
	_d = d;
}

void Simple_Pid::set_p(double p)
{
	_p = p;
}

double Simple_Pid::get_p()
{
	return _p;
}

void Simple_Pid::set_i(double i)
{
	_i = i;
}

double Simple_Pid::get_i()
{
	return _i;
}

void Simple_Pid::set_d(double d)
{
	_d = d;
}

double Simple_Pid::get_d()
{
	return _d;
}

void Simple_Pid::set_target_value(double target_value)
{
	_target_value = target_value;
}

double Simple_Pid::get_target_value()
{
	return _target_value;
}

void Simple_Pid::set_max_output(double max_output)
{
	_max_output = max_output;
}

double Simple_Pid::get_max_output()
{
	return _max_output;
}

void Simple_Pid::set_min_output(double min_output)
{
	_min_output = min_output;
}

double Simple_Pid::get_min_output()
{
	return _min_output;
}

double Simple_Pid::calc_output(double input, double timestamp_in_millis) 
{
	double error = _target_value - input;
	double delta_time = (timestamp_in_millis - _previous_timestamp) / 1000;

	// extreme edge case of double overflow is unhandled
	if (
		_integral + error * delta_time <= _max_output &&
		_integral + error * delta_time >= _min_output
	) {
		_integral += error * delta_time;
	};
	
	double derivative = (error - _previous_error) / delta_time;

	double output = _target_value * (1 + (_p * error + _i * _integral + _d * derivative));
	
	_previous_error = error;
	_previous_timestamp = timestamp_in_millis;

	return output;
}
