#include <iostream>

#include "Towers/AirProjectile.h"
#include "Towers/AirTower.h"
#include "Towers/Projectile.h"
#include "Map/PathTile.h"
#include "EnviormentUnits/EnviormentUnit.h"
#include "ViewModels/ProjectileVM.h"
#include "Map/SolidGroundTile.h"

AirProjectile::AirProjectile
(AirTower* origin, PathTile* target, uint flyingHitpoint, uint nonflyingHitpoints) :
 Projectile(origin, target, 50, flyingHitpoint), _nonFlyingHitPoints(nonflyingHitpoints)
{

}

AirProjectile::~AirProjectile(){}

double AirProjectile::_OnImpact(){
	std::vector<EnviormentUnit*> units = _target->GetUnits();
	bool hit = false;
	double exp = 0;
	for (auto it = units.begin(); it != units.end() && !hit; ++it){
		
		hit = true;

		uint currentHP = (*it)->GetHP();


		uint hitPoints = _hitPoints;
		if (!(*it)->Flies()){
			hitPoints = _nonFlyingHitPoints;
		}

		(*it)->GetHit(hitPoints);
		(*it)->PushBack();

		exp += hitPoints;

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

ProjectileVM AirProjectile::GetViewModel(){
	ProjectileVM vm;
	vm.type = pAir;
	vm.distanceToCover = _distance;
	vm.distanceCovered = _distanceCovered;
	vm.fromXpos = _origin->GetPosition()->GetXPos();
	vm.fromYpos = _origin->GetPosition()->GetYPos();
	vm.toXpos = _target->GetXPos();
	vm.toYpos = _target->GetYPos();
	return vm;
}