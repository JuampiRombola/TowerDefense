#include <iostream>

#include "Map/Map.h"
#include "Towers/FireProjectile.h"
#include "Towers/Projectile.h"
#include "Towers/FireTower.h"
#include "EnviormentUnits/EnviormentUnit.h"

FireProjectile::FireProjectile
(FireTower* origin, PathTile* target, uint hitpoints, 
	uint collateralRange, uint collateralDamage) :
 Projectile(origin, target, 50, hitpoints), _collateralRange(collateralRange),
 _collateralDamage(collateralDamage)
{

}

FireProjectile::~FireProjectile(){}



uint FireProjectile::_OnImpact(){
	std::vector<PathTile*> tilesInRange = _target->GetMap()->GetTilesInRange(_target, _collateralRange);
	std::vector<EnviormentUnit*> unitsInTargetTile = _target->GetUnits();
	bool hit = false;

	EnviormentUnit* targetUnit = NULL;
	if (unitsInTargetTile.size() != 0){
		targetUnit = *(unitsInTargetTile.begin());
		targetUnit->GetHit(_hitPoints);
		hit = true;
		std::cout << "Fire Projectile target tile hit!!\n" << std::flush;
	}

	for (auto it = unitsInTargetTile.begin(); it != unitsInTargetTile.end(); ++it){
		if (*it != targetUnit){
			// No le doy bola al target porque ya le pegue, 
			// ahora le pego a los demas del target tile
			std::cout << "Fire Projectile collateral hit IN SAME TILE!!\n" << std::flush;
			(*it)->GetHit(_collateralDamage);
		}
	}

	for (auto it = tilesInRange.begin(); it != tilesInRange.end(); ++it){
		if (*it != _target){
			// No le doy bola al target tile porque ya les pegue
			std::vector<EnviormentUnit*> unitsInTile = (*it)->GetUnits();
			for (auto it2 = unitsInTile.begin(); it2 != unitsInTile.end(); ++it2){
				(*it2)->GetHit(_collateralDamage);
				std::cout << "Fire Projectile collateral hit!!\n" << std::flush;
			}
		}
	}

	if (!hit)
		std::cout << "Fire Projectile did not hit anything on target tile!!\n" << std::flush;

	return 0;
}