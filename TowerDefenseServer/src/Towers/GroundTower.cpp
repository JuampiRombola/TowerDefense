#include <iostream>

#include <memory>

#include "Towers/Tower.h"
#include "Towers/Projectile.h"
#include "Towers/GroundTower.h"
#include "Map/SolidGroundTile.h"
#include "Towers/GroundProjectile.h"

GroundTower::GroundTower(uint cooldown_sec, uint range, std::shared_ptr<SolidGroundTile> position, Map* map)
: Tower(cooldown_sec, range, position, map) {}

GroundTower::~GroundTower(){}



void GroundTower::PrintDebug(){

}

std::shared_ptr<Projectile> GroundTower::_BuildProjectile(std::shared_ptr<PathTile> target){
	return std::shared_ptr<Projectile>(new GroundProjectile(_position, target, 10));
}
