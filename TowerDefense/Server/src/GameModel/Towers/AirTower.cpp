#include <iostream>
#include <cmath>

#include "../../../include/GameModel/Commands/BuildTowerCommand.h"
#include "../../../include/GameModel/Towers/Tower.h"
#include "../../../include/GameModel/Towers/Projectile.h"
#include "../../../include/GameModel/Towers/AirTower.h"
#include "../../../include/GameModel/Map/SolidGroundTile.h"
#include "../../../include/GameModel/Towers/AirProjectile.h"
#include <yaml-cpp/yaml.h>
#include "../../../include/GameModel/Commands/UpgradeTowerCommand.h"
#include "../../../include/GameModel/ViewModels/TowerVM.h"


AirTower::AirTower(uint cooldown_sec, uint range, uint damage, uint nonflyingDamage, SolidGroundTile* position, Map* map)
: Tower(cooldown_sec, range, damage, position, map), _nonFlyingDamage(nonflyingDamage) {}

AirTower::~AirTower(){}

void AirTower::PrintDebug(){

}

Projectile* AirTower::_BuildProjectile(PathTile* target){
	return new AirProjectile(this, target, _damage, _nonFlyingDamage);
}

bool AirTower::Upgrade(const YAML::Node& cfg, UpgradeType type){
	switch (type){
		case Range:
			{
				uint rangeIncrease = cfg["towers"]["air"]["upgrade_range_increase"].as<uint>();
				uint mult = cfg["towers"]["air"]["upgrade_range_mult"].as<uint>();
				double base = cfg["towers"]["air"]["upgrade_range_base"].as<double>();
				double expRequired = pow(base, _upgradeLevel);
				expRequired *= mult;
				if (_experience >= expRequired){
					_experience -= expRequired;
					_range += rangeIncrease;
					_upgradeLevel++;
					std::cout << "AirTower range Upgraded\n" << std::flush;
					return true;
				}
				std::cout << "AirTower needs more xp to Upgrade range\n" << std::flush;
			}
		break;
		case Damage:
			{
				uint flyingTargetDamageIncrease = cfg["towers"]["air"]["upgrade_flying_target_damage_increase"].as<uint>();
				uint nonFlyingDamageDamageIncrease = cfg["towers"]["air"]["upgrade_non_flying_target_damage_increase"].as<uint>();
				uint mult = cfg["towers"]["air"]["upgrade_damage_mult"].as<uint>();
				double base = cfg["towers"]["air"]["upgrade_damage_base"].as<double>();
				double expRequired = pow(base, _upgradeLevel);
				expRequired *= mult;
				if (_experience > expRequired){
					_experience -= expRequired;
					_nonFlyingDamage += nonFlyingDamageDamageIncrease;
					_damage += flyingTargetDamageIncrease;
					_upgradeLevel++;
					return true;
				}		
			}
			break;
		case CollateralRange:
			return false;
		case Slow:
			return false; 
	}
	return false;
}

TowerVM AirTower::GetViewModel(){
	TowerVM vm;
	vm.type = Air;
	vm.xPos = _position->GetXPos();
	vm.yPos = _position->GetYPos();
	vm.experience = _experience;
	vm.level = _upgradeLevel;
	return vm;
}