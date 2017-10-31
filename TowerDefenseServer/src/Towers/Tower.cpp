#include <iostream>	
#include <vector>

#include "../../include/Towers/Tower.h"
#include "../../include/EnviormentUnits/EnviormentUnit.h"
#include "../../include/Map/Map.h"
#include "../../include/Helpers.h"

Tower::Tower(uint cooldown_ms, uint range, uint damage, SolidGroundTile* pos, Map* map) : 
_lastTimeStamp_ms(0), _cooldown_ms(cooldown_ms), _map(map), _position(pos), _range(range), _experience(0), _damage(damage),
_upgradeLevel(1) {

}

Tower::~Tower(){

}



bool Tower::_CanFire(){
	if (_lastTimeStamp_ms == 0)
		return true;

	uint delta = Helpers::MillisecondsTimeStamp() - _lastTimeStamp_ms;

	return (delta > _cooldown_ms);
}


Projectile* Tower::Step(){
	if (_CanFire()){
		EnviormentUnit* targetUnit = _GetTargetUnitInRange();
		if (targetUnit != nullptr)
			return _Fire(targetUnit);
	}

	return nullptr;
}


EnviormentUnit* Tower::_GetTargetUnitInRange(){
	std::vector<EnviormentUnit*> units = _map->GetUnitsInRadius(_range, _position);
	if (units.size() == 0)
		return nullptr;

	//De todos los que tengo en rango agarro el primero que encuentro.
	return *(units.begin());
}



Projectile* Tower::_Fire(EnviormentUnit* target){
	std::cout << "TOWER FIRE!!!\n" << std::flush;
	_lastTimeStamp_ms = Helpers::MillisecondsTimeStamp();
	return _BuildProjectile(target->GetPosition());
}


void Tower::AddExperience(double exp){
	_experience += exp;
}

void Tower::AddDamage(uint damage){
	_damage += damage;
}

SolidGroundTile* Tower::GetPosition(){
	return _position;
}
