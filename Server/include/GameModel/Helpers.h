
#ifndef __HELPERS__
#define __HELPERS__

#include <chrono>

class Helpers{

public:

	static unsigned long long MillisecondsTimeStamp(){
		typedef std::chrono::steady_clock clk;
		unsigned long long milliseconds_since_epoch =
		std::chrono::duration_cast<std::chrono::milliseconds>(
			clk::now().time_since_epoch()).count();
		return milliseconds_since_epoch;
	}

};

#endif



