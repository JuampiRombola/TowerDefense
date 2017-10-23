#include <iostream>

#include <memory>

#include "Towers/Tower.h"
#include "Towers/Projectile.h"
#include "Towers/WindTower.h"
#include "Map/SolidGroundTile.h"
#include "Towers/WindProjectile.h"

WindTower::WindTower(uint cooldown_sec, uint range, std::shared_ptr<SolidGroundTile> position, Map* map)
: Tower(cooldown_sec, range, position, map) {}

WindTower::~WindTower(){}



void WindTower::PrintDebug(){

}

std::shared_ptr<Projectile> WindTower::_BuildProjectile(std::shared_ptr<PathTile> target){
	return std::shared_ptr<Projectile>(new WindProjectile(_position, target, 10));
}
