#include <iostream>

#include "../../include/Map/SolidGroundTile.h"
#include "../../include/Towers/GroundProjectile.h"
#include "../../include/Towers/GroundTower.h"
#include "../../include/Towers/Projectile.h"
#include "../../include/Map/PathTile.h"
#include "../../include/EnviormentUnits/EnviormentUnit.h"
#include "../../include/ViewModels/ProjectileVM.h"

GroundProjectile::GroundProjectile
(GroundTower* tower, PathTile* target, uint hitpoints) :
 Projectile(tower, target, 50, hitpoints)
{

}

GroundProjectile::~GroundProjectile(){}



double GroundProjectile::_OnImpact(){
	std::vector<EnviormentUnit*> units = _target->GetUnits();
	bool hit = false;
	double exp = 0;
	for (auto it = units.begin(); it != units.end() && !hit; ++it){
		if (!(*it)->Flies()){


			uint currentHP = (*it)->GetHP();

			(*it)->GetHit(_hitPoints);

			exp += _hitPoints;

			if (!((*it)->IsAlive())){
				exp += currentHP / 2;
			}

			hit = true;
		}
	}

	if (!hit) {		
		std::cout << "Ground Projectile missed!!\n" << std::flush;
		return 0;
	}	

	return exp;;
}

ProjectileVM GroundProjectile::GetViewModel(){
	ProjectileVM vm;
	vm.type = pGround;
	vm.distanceToCover = _distance;
	vm.distanceCovered = _distanceCovered;
	vm.fromXpos = _origin->GetPosition()->GetXPos();
	vm.fromYpos = _origin->GetPosition()->GetYPos();
	vm.toXpos = _target->GetXPos();
	vm.toYpos = _target->GetYPos();
	return vm;
}