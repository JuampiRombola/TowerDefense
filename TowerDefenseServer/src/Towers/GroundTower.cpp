#include <iostream>

#include "Towers/Tower.h"
#include "Towers/Projectile.h"
#include "Towers/GroundTower.h"
#include "Map/SolidGroundTile.h"
#include "Towers/GroundProjectile.h"
#include "yaml-cpp/yaml.h"
#include "Commands/UpgradeTowerCommand.h"


GroundTower::GroundTower(uint cooldown_sec, uint range, uint damage, SolidGroundTile* position, Map* map)
: Tower(cooldown_sec, range, damage, position, map) {}

GroundTower::~GroundTower(){}



void GroundTower::PrintDebug(){

}

Projectile* GroundTower::_BuildProjectile(PathTile* target){
	return new GroundProjectile(this, target, 10);
}

bool GroundTower::Upgrade(const YAML::Node& cfg, UpgradeType type){
	return false;
}