#include <iostream>


#include "Towers/WindProjectile.h"
#include "Towers/WindTower.h"
#include "Towers/Projectile.h"
#include "Map/PathTile.h"
#include "EnviormentUnits/EnviormentUnit.h"

WindProjectile::WindProjectile
(WindTower* origin, PathTile* target, uint hitpoints) :
 Projectile(origin, target, 50, hitpoints)
{

}

WindProjectile::~WindProjectile(){}



uint WindProjectile::_OnImpact(){
	std::vector<EnviormentUnit*> units = _target->GetUnits();
	bool hit = false;
	uint exp = 0;
	for (auto it = units.begin(); it != units.end() && !hit; ++it){
		
		hit = true;

		uint currentHP = (*it)->GetHP();


		uint hitPoints = _hitPoints;
		if (!(*it)->Flies()){
			hitPoints *= 5;
		}

		(*it)->GetHit(hitPoints);
		(*it)->PushBack();

		exp += hitPoints;

		if (!((*it)->IsAlive())){
			exp += currentHP / 2;
		}

	}

	if (!hit) {		
		std::cout << "Wind Projectile missed!!\n" << std::flush;
		return 0;
	}	

	return exp;;
}