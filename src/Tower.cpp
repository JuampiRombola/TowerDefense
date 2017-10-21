#include <chrono>

#include "Tower.h"


Tower::Tower(unsigned int cooldown_sec) : 
_lastTimeStamp_ms(0), _cooldown_sec(cooldown_sec) {

}

Tower::~Tower(){

}

bool Tower::_CanFire(){
	if (_lastTimeStamp_ms == 0)
		return true;

	typedef std::chrono::steady_clock clk;
	unsigned long long milliseconds_since_epoch =
	std::chrono::duration_cast<std::chrono::milliseconds>(
		clk::now().time_since_epoch()).count();

	unsigned long long cooldown_ms = _cooldown_sec * 1000;

	unsigned long long delta =
	milliseconds_since_epoch - _lastTimeStamp_ms;

	bool canfire = delta > cooldown_ms;

	if (canfire){
	_lastTimeStamp_ms = milliseconds_since_epoch;
	}

	return canfire;

}

