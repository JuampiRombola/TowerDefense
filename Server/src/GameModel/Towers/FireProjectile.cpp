#include <iostream>

#include "../../../include/GameModel/Map/Map.h"
#include "../../../include/GameModel/Towers/FireProjectile.h"
#include "../../../include/GameModel/Towers/Projectile.h"
#include "../../../include/GameModel/Towers/FireTower.h"
#include "../../../include/GameModel/EnviormentUnits/EnviormentUnit.h"
#include "../../../include/GameModel/ViewModels/ProjectileVM.h"
#include "../../../include/GameModel/Map/SolidGroundTile.h"

FireProjectile::FireProjectile
(FireTower* origin, PathTile* target, uint hitpoints, 
	uint collateralRange, uint collateralDamage, uint speed_ms) :
 Projectile(origin, target, speed_ms, hitpoints), _collateralRange(collateralRange),
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
	vm.type = SPELL_TYPE_FIRE;
	vm.flight_duration_ms = _distance * _ms_over_tile;
	vm.fromXpos = _origin->GetPosition()->GetXPos();
	vm.fromYpos = _origin->GetPosition()->GetYPos();
	vm.toXpos = _target->GetXPos();
	vm.toYpos = _target->GetYPos();
	return vm;
}