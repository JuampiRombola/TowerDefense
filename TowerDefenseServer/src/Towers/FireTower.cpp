#include <iostream>
#include <cmath>

#include "../../include/Towers/Tower.h"
#include "../../include/Towers/Projectile.h"
#include "../../include/Towers/FireTower.h"
#include "../../include/Map/SolidGroundTile.h"
#include "../../include/Towers/FireProjectile.h"
#include "../../include/yaml-cpp/yaml.h"
#include "../../include/Commands/UpgradeTowerCommand.h"
#include "../../include/ViewModels/TowerVM.h"
#include "../../include/Commands/BuildTowerCommand.h"

FireTower::FireTower(uint cooldown_ms, uint range, uint damage, 
	SolidGroundTile* position, Map* map, uint collateralDamage, uint collateralRange)
: Tower(cooldown_ms, range, damage, position, map), _collateralDamage(collateralDamage), _collateralRange(collateralRange) {}

FireTower::~FireTower(){}



void FireTower::PrintDebug(){

}

Projectile* FireTower::_BuildProjectile(PathTile* target){
	return new FireProjectile(this, target, _damage, _collateralRange, _collateralDamage);
}

bool FireTower::Upgrade(const YAML::Node& cfg, UpgradeType type){
	switch (type){
		case Range:
			{
				uint rangeIncrease = cfg["towers"]["fire"]["upgrade_range_increase"].as<uint>();
				uint mult = cfg["towers"]["fire"]["upgrade_range_mult"].as<uint>();
				double base = cfg["towers"]["fire"]["upgrade_range_base"].as<double>();
				double expRequired = pow(base, _upgradeLevel);
				expRequired *= mult;
				if (_experience >= expRequired){
					_experience -= expRequired;
					_range += rangeIncrease;
					_upgradeLevel++;
					std::cout << "firetower range Upgraded\n" << std::flush;
					return true;
				}
				std::cout << "firetower needs more xp to Upgrade range\n" << std::flush;
			}
		break;
		case Damage:
			{
				uint damageIncrease = cfg["towers"]["fire"]["upgrade_damage_increase"].as<uint>();
				uint collateralDamageIncrease = cfg["towers"]["fire"]["upgrade_collateral_damage_increase"].as<uint>();
				uint mult = cfg["towers"]["fire"]["upgrade_damage_mult"].as<uint>();
				double base = cfg["towers"]["fire"]["upgrade_damage_base"].as<double>();
				double expRequired = pow(base, _upgradeLevel);
				expRequired *= mult;
				if (_experience > expRequired){
					_experience -= expRequired;
					_damage += damageIncrease;
					_collateralDamage += collateralDamageIncrease;
					_upgradeLevel++;
					return true;
				}		
			}
			break;
		case CollateralRange:
			{
				uint collateralRangeIncrease = cfg["towers"]["fire"]["upgrade_collateral_range_increase"].as<uint>();
				uint mult = cfg["towers"]["fire"]["upgrade_collateral_range_mult"].as<uint>();
				double base = cfg["towers"]["fire"]["upgrade_collateral_range_base"].as<double>();
				double expRequired = pow(base, _upgradeLevel);
				expRequired *= mult;
				if (_experience > expRequired){
					_experience -= expRequired;
					_collateralRange += collateralRangeIncrease;
					_upgradeLevel++;
					return true;
				}		
			}		
		case Slow:
			return false; 
	}
	return false;
}

TowerVM FireTower::GetViewModel(){
	TowerVM vm;
	vm.type = Air;
	vm.xPos = _position->GetXPos();
	vm.yPos = _position->GetYPos();
	vm.experience = _experience;
	vm.level = _upgradeLevel;
	return vm;
}