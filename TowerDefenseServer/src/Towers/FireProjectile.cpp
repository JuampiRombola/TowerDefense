#include <iostream>

#include "Map/Map.h"
#include "Towers/FireProjectile.h"
#include "Towers/Projectile.h"
#include "Towers/FireTower.h"
#include "EnviormentUnits/EnviormentUnit.h"
#include "ViewModels/ProjectileVM.h"
#include "Map/SolidGroundTile.h"

FireProjectile::FireProjectile
(FireTower* origin, PathTile* target, uint hitpoints, 
	uint collateralRange, uint collateralDamage) :
 Projectile(origin, target, 50, hitpoints), _collateralRange(collateralRange),
 _collateralDamage(collateralDamage)
{

}

FireProjectile::~FireProjectile(){}



double FireProjectile::_OnImpact(){
	std::vector<PathTile*> tilesInRange = _target->GetMap()->GetPathTilesInRange(_target, _collateralRange);
	std::vector<EnviormentUnit*> unitsInTargetTile = _target->GetUnits();
	bool hit = false;
	double exp = 0;

	EnviormentUnit* targetUnit = nullptr;
	if (unitsInTargetTile.size() != 0){
		targetUnit = *(unitsInTargetTile.begin());

		uint currentHP = targetUnit->GetHP();
		exp += _hitPoints;

		if (!(targetUnit->IsAlive())){
			exp += currentHP / 2;
		}

		targetUnit->GetHit(_hitPoints);
		hit = true;
		std::cout << "Fire Projectile target tile hit!!\n" << std::flush;
	}

	for (auto it = unitsInTargetTile.begin(); it != unitsInTargetTile.end(); ++it){
		if (*it != targetUnit){
			// No le doy bola al target porque ya le pegue, 
			// ahora le pego a los demas del target tile
			std::cout << "Fire Projectile collateral hit IN SAME TILE!!\n" << std::flush;
			uint currentHP = (*it)->GetHP();
			(*it)->GetHit(_collateralDamage);
			exp += _collateralDamage;
			if (!((*it)->IsAlive())){
				exp += currentHP / 2;
			}

		}
	}

	for (auto it = tilesInRange.begin(); it != tilesInRange.end(); ++it){
		if (*it != _target){
			// No le doy bola al target tile porque ya les pegue
			std::vector<EnviormentUnit*> unitsInTile = (*it)->GetUnits();
			for (auto it2 = unitsInTile.begin(); it2 != unitsInTile.end(); ++it2){
				uint currentHP = (*it2)->GetHP();
				(*it2)->GetHit(_collateralDamage);
				exp += _collateralDamage;
				if (!((*it2)->IsAlive())){
					exp += currentHP / 2;
				}
				std::cout << "Fire Projectile collateral hit!!\n" << std::flush;
			}
		}
	}

	if (!hit)
		std::cout << "Fire Projectile did not hit anything on target tile!!\n" << std::flush;

	return exp;
}

ProjectileVM FireProjectile::GetViewModel(){
	ProjectileVM vm;
	vm.type = pFire;
	vm.distanceToCover = _distance;
	vm.distanceCovered = _distanceCovered;
	vm.fromXpos = _origin->GetPosition()->GetXPos();
	vm.fromYpos = _origin->GetPosition()->GetYPos();
	vm.toXpos = _target->GetXPos();
	vm.toYpos = _target->GetYPos();
	return vm;
}