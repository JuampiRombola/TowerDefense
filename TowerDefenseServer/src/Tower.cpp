#include <chrono>
#include <iostream>	

#include "Tower.h"


Tower::Tower(uint cooldown_sec, uint range, SolidGroundTile* pos, Map* map) : 
_lastTimeStamp_ms(0), _cooldown_sec(cooldown_sec), _map(map), _position(pos), _range(range) {

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


Projectile* Tower::Step(){
	if (_CanFire())
		return _Fire();
	else
		std::cout << "still on cooldown";
	return NULL;
}

Projectile* Tower::_Fire(){
	std::vector<EnviormentUnit*> units = _map->GetUnitsInRadius(_range, _position);
	if (units.size() > 0){
		std::cout << units.size() << " UNITS IN RANGE\n" << std::flush;
		EnviormentUnit* targetunit = *units.begin();
		return _BuildProjectile(targetunit->GetPosition());
	}
	return NULL;
}
