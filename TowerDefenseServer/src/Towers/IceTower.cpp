#include <iostream>

#include <memory>

#include "Towers/Tower.h"
#include "Towers/Projectile.h"
#include "Towers/IceTower.h"
#include "Map/SolidGroundTile.h"
#include "Towers/IceProjectile.h"

IceTower::IceTower(uint cooldown_sec, uint range, uint damage, std::shared_ptr<SolidGroundTile> position, Map* map)
: Tower(cooldown_sec, range, damage, position, map) {}

IceTower::~IceTower(){}



void IceTower::PrintDebug(){

}

std::shared_ptr<Projectile> IceTower::_BuildProjectile(std::shared_ptr<PathTile> target){
	return std::shared_ptr<Projectile>(new IceProjectile(this, target, 10));
}
