#include <iostream>
#include <memory>

#include "GroundProjectile.h"
#include "Projectile.h"
#include "PathTile.h"
#include "EnviormentUnit.h"

GroundProjectile::GroundProjectile
(std::shared_ptr<SolidGroundTile> origin, std::shared_ptr<PathTile> target, uint hitpoints) :
 Projectile(origin, target, 5, hitpoints)
{

}

GroundProjectile::~GroundProjectile(){}



void GroundProjectile::_OnImpact(){
	std::vector<std::shared_ptr<EnviormentUnit>> units = _target->GetUnits();
	bool hit = false;
	for (auto it = units.begin(); it != units.end() && !hit; ++it){
		if (!(*it).get()->Flies()){
			(*it).get()->GetHit(_hitPoints);
			hit = true;
		}
	}

	if (!hit)
		std::cout << "Projectile missed!!\n" << std::flush;


}