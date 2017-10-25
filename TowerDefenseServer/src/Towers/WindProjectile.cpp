#include <iostream>
#include <memory>

#include "Towers/WindProjectile.h"
#include "Towers/WindTower.h"
#include "Towers/Projectile.h"
#include "Map/PathTile.h"
#include "EnviormentUnits/EnviormentUnit.h"

WindProjectile::WindProjectile
(WindTower* origin, std::shared_ptr<PathTile> target, uint hitpoints) :
 Projectile(origin, target, 50, hitpoints)
{

}

WindProjectile::~WindProjectile(){}



uint WindProjectile::_OnImpact(){
	std::vector<std::shared_ptr<EnviormentUnit>> units = _target->GetUnits();
	bool hit = false;
	uint exp = 0;
	for (auto it = units.begin(); it != units.end() && !hit; ++it){
		
		hit = true;

		uint currentHP = (*it).get()->GetHP();


		uint hitPoints = _hitPoints;
		if (!(*it).get()->Flies()){
			hitPoints *= 5;
		}

		(*it).get()->GetHit(hitPoints);
		(*it).get()->PushBack(*it);

		exp += hitPoints;

		if (!((*it).get()->IsAlive())){
			exp += currentHP / 2;
		}

	}

	if (!hit) {		
		std::cout << "Wind Projectile missed!!\n" << std::flush;
		return 0;
	}	

	return exp;;
}