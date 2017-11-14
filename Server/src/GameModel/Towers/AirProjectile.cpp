#include <iostream>

#include "../../../include/GameModel/Towers/AirProjectile.h"
#include "../../../include/GameModel/Towers/AirTower.h"
#include "../../../include/GameModel/Towers/Projectile.h"
#include "../../../include/GameModel/Map/PathTile.h"
#include "../../../include/GameModel/EnviormentUnits/EnviormentUnit.h"
#include "../../../include/GameModel/ViewModels/ProjectileVM.h"
#include "../../../include/GameModel/Map/SolidGroundTile.h"

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
	vm.type = SPELL_TYPE_AIR;
	vm.distanceToCover = _distance;
	vm.distanceCovered = _distanceCovered;
	vm.fromXpos = _origin->GetPosition()->GetXPos();
	vm.fromYpos = _origin->GetPosition()->GetYPos();
	vm.toXpos = _target->GetXPos();
	vm.toYpos = _target->GetYPos();
	return vm;
}