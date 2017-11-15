#include <iostream>

#include "../../../include/GameModel/Map/SolidGroundTile.h"
#include "../../../include/GameModel/Towers/GroundProjectile.h"
#include "../../../include/GameModel/Towers/GroundTower.h"
#include "../../../include/GameModel/Towers/Projectile.h"
#include "../../../include/GameModel/Map/PathTile.h"
#include "../../../include/GameModel/EnviormentUnits/EnviormentUnit.h"
#include "../../../include/GameModel/ViewModels/ProjectileVM.h"

GroundProjectile::GroundProjectile
(GroundTower* tower, PathTile* target, uint hitpoints) :
 Projectile(tower, target, 500, hitpoints)
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
	vm.type = SPELL_TYPE_GROUND;
	vm.distanceToCover = _distance;
	vm.distanceCovered = _distanceCovered;
	vm.fromXpos = _origin->GetPosition()->GetXPos();
	vm.fromYpos = _origin->GetPosition()->GetYPos();
	vm.toXpos = _target->GetXPos();
	vm.toYpos = _target->GetYPos();
	return vm;
}