#include <iostream>

#include "../../../include/GameModel/Map/SolidGroundTile.h"
#include "../../../include/GameModel/Towers/WaterProjectile.h"
#include "../../../include/GameModel/Towers/Projectile.h"
#include "../../../include/GameModel/Towers/WaterTower.h"
#include "../../../include/GameModel/Map/PathTile.h"
#include "../../../include/GameModel/EnviormentUnits/EnviormentUnit.h"
#include "../../../include/GameModel/ViewModels/ProjectileVM.h"

WaterProjectile::WaterProjectile
(WaterTower* origin, PathTile* target, uint hitpoints, uint slowDuration_sec, uint slowPercent) :
 Projectile(origin, target, 50, hitpoints), _slowDuration_sec(slowDuration_sec), _slowPercent(slowPercent)
{

}

WaterProjectile::~WaterProjectile(){}



double WaterProjectile::_OnImpact(){
	std::vector<EnviormentUnit*> units = _target->GetUnits();
	bool hit = false;
	double exp = 0;
	for (auto it = units.begin(); it != units.end() && !hit; ++it){
		
		hit = true;

		uint currentHP = (*it)->GetHP();

		EnviormentUnit* unit = (*it);
		unit->GetHit(_hitPoints);

		int slowSeconds = _slowDuration_sec;
		int percentSlow = _slowPercent;
		unit->Slow( slowSeconds, percentSlow );

		exp = _hitPoints;

		if (!((*it)->IsAlive())){
			exp += currentHP / 2;
		}

	}

	if (!hit) {		
		std::cout << "Air Projectile missed!!\n" << std::flush;
		return 0;
	}	

	return exp;;
}

ProjectileVM WaterProjectile::GetViewModel(){
	ProjectileVM vm;
	vm.type = SPELL_TYPE_WATER;
	vm.distanceToCover = _distance;
	vm.distanceCovered = _distanceCovered;
	vm.fromXpos = _origin->GetPosition()->GetXPos();
	vm.fromYpos = _origin->GetPosition()->GetYPos();
	vm.toXpos = _target->GetXPos();
	vm.toYpos = _target->GetYPos();
	return vm;
}

