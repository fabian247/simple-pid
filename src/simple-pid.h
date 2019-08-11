#if !defined(SIMPLE_PID_H)
#define SIMPLE_PID_H

#include <array>

namespace simple_pid 
{
	class Simple_Pid {
		double _p, _i, _d;
		double _target_value;
		double _max_output;
		double _min_output;
		double _previous_error;
		double _previous_timestamp;
		double _integral;
		
		public:
			Simple_Pid(double target_valuel, double p, double i, double d, double initial_timestamp);

			void set_target_value(double value);
			double get_target_value();

			void set_max_output(double max_output);
			double get_max_output();			

			void set_min_output(double min_output);
			double get_min_output();			
			
			void set_p(double p);
			double get_p();

			void set_i(double i);
			double get_i();

			void set_d(double d);
			double get_d();
			
			double calc_output(double input, double timestamp_in_millis);
	};
}

#endif
