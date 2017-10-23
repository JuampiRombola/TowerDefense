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

	static bool TimeElapsed(unsigned long long lastTimeStamp, uint msToWait){
		unsigned long long current = Helpers::MillisecondsTimeStamp();
		unsigned long long delta = current - lastTimeStamp;
		if (delta < msToWait)
			return false;
		else 
			return true;
	}

};



