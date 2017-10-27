#include <iostream>


#include "Towers/GroundProjectile.h"
#include "Towers/GroundTower.h"
#include "Towers/Projectile.h"
#include "Map/PathTile.h"
#include "EnviormentUnits/EnviormentUnit.h"

GroundProjectile::GroundProjectile
(GroundTower* tower, PathTile* target, uint hitpoints) :
 Projectile(tower, target, 50, hitpoints)
{

}

GroundProjectile::~GroundProjectile(){}



uint GroundProjectile::_OnImpact(){
	std::vector<EnviormentUnit*> units = _target->GetUnits();
	bool hit = false;
	uint exp = 0;
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