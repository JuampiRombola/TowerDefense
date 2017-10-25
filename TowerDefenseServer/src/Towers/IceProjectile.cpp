#include <iostream>
#include <memory>

#include "Towers/IceProjectile.h"
#include "Towers/Projectile.h"
#include "Towers/IceTower.h"
#include "Map/PathTile.h"
#include "EnviormentUnits/EnviormentUnit.h"

IceProjectile::IceProjectile
(IceTower* origin, std::shared_ptr<PathTile> target, uint hitpoints) :
 Projectile(origin, target, 50, hitpoints)
{

}

IceProjectile::~IceProjectile(){}



uint IceProjectile::_OnImpact(){
	std::vector<std::shared_ptr<EnviormentUnit>> units = _target->GetUnits();
	bool hit = false;
	uint exp = 0;
	for (auto it = units.begin(); it != units.end() && !hit; ++it){
		
		hit = true;

		uint currentHP = (*it).get()->GetHP();

		EnviormentUnit* unit = (*it).get();
		unit->GetHit(_hitPoints);

		int slowSeconds = 6;
		int percentSlow = 185;
		unit->Slow( slowSeconds, percentSlow);

		exp = _hitPoints;

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