#include <iostream>	
#include <vector>
#include <cmath>

#include "../../../include/GameModel/Towers/Tower.h"
#include "../../../include/GameModel/EnviormentUnits/EnviormentUnit.h"
#include "../../../include/GameModel/Map/Map.h"
#include "../../../include/GameModel/Helpers.h"
#include "../../../include/GameModel/GameNotifications/TowerGainedExperienceGameNotification.h"

Tower::Tower(uint cooldown_ms, uint range, uint damage, SolidGroundTile* pos, Map* map, uint projectile_ms_over_tile, ThreadSafeQueue<GameNotification*>& notifications) :
_lastTimeStamp_ms(0), _cooldown_ms(cooldown_ms), _map(map), _position(pos), _range(range), _experience(0), _damage(damage),
_upgradeLevel(1), _projectile_ms_over_tile(projectile_ms_over_tile), _notifications(notifications) {

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
		EnviormentUnit* targetUnit = _GetTargetUnitInRange(GetTowerType());
		if (targetUnit != nullptr)
			return _Fire(targetUnit);

	}

	return nullptr;
}


EnviormentUnit* Tower::_GetTargetUnitInRange(TowerType type){
	std::vector<EnviormentUnit*> units = _map->GetUnitsInRadius(_range, _position);
	if (units.size() == 0)
		return nullptr;

	//De todos los que tengo en rango agarro el primero que encuentro.
	if (type != Ground)
		return *(units.begin());
	else{
		for (auto it = units.begin(); it != units.end(); ++it){
			EnviormentUnit* unit = *it;
			if (!unit->Flies())
				return unit;
		}
	}

	return nullptr;
}



Projectile* Tower::_Fire(EnviormentUnit* target){
	_lastTimeStamp_ms = Helpers::MillisecondsTimeStamp();
	return _BuildProjectile(target->GetPosition());
}

void Tower::AddExperience(double exp){
	if (exp == 0)
		return;
	_notifications.Queue(new TowerGainedExperienceGameNotification(_position->GetXPos(), _position->GetYPos(), _experience ));
	_experience += exp;
}


SolidGroundTile* Tower::GetPosition(){
	return _position;
}
