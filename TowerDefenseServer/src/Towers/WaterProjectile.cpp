#include <iostream>

#include "Map/SolidGroundTile.h"
#include "Towers/WaterProjectile.h"
#include "Towers/Projectile.h"
#include "Towers/WaterTower.h"
#include "Map/PathTile.h"
#include "EnviormentUnits/EnviormentUnit.h"
#include "ViewModels/ProjectileVM.h"

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
	vm.type = pWater;
	vm.distanceToCover = _distance;
	vm.distanceCovered = _distanceCovered;
	vm.fromXpos = _origin->GetPosition()->GetXPos();
	vm.fromYpos = _origin->GetPosition()->GetYPos();
	vm.toXpos = _target->GetXPos();
	vm.toYpos = _target->GetYPos();
	return vm;
}

