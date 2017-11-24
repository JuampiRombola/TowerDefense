#include <iostream>
#include <cmath>

#include "../../../include/GameModel/Towers/Tower.h"
#include "../../../include/GameModel/Towers/Projectile.h"
#include "../../../include/GameModel/Towers/FireTower.h"
#include "../../../include/GameModel/Map/SolidGroundTile.h"
#include "../../../include/GameModel/Towers/FireProjectile.h"
#include <yaml-cpp/yaml.h>
#include "../../../include/GameModel/Commands/UpgradeTowerCommand.h"
#include "../../../include/GameModel/ViewModels/TowerVM.h"
#include "../../../include/GameModel/Commands/BuildTowerCommand.h"

FireTower::FireTower(uint cooldown_ms, uint range, uint damage, 
	SolidGroundTile* position, Map* map, uint collateralDamage, uint collateralRange,
	uint projectile_ms_over_tile, ThreadSafeQueue<GameNotification*>& notifications)
: Tower(cooldown_ms, range, damage, position, map, projectile_ms_over_tile, notifications), _collateralDamage(collateralDamage), _collateralRange(collateralRange) {}

FireTower::~FireTower(){}



void FireTower::PrintDebug(){

}

Projectile* FireTower::_BuildProjectile(PathTile* target){
	return new FireProjectile(this, target, _damage, _collateralRange, _collateralDamage, _projectile_ms_over_tile);
}

bool FireTower::Upgrade(UpgradeType type){
	switch (type){
		case Range:
			{
				uint rangeIncrease = (*cfg)["towers"]["fire"]["upgrade_range_increase"].as<uint>();
				uint mult = (*cfg)["towers"]["fire"]["upgrade_range_mult"].as<uint>();
				double base = (*cfg)["towers"]["fire"]["upgrade_range_base"].as<double>();
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
				uint damageIncrease = (*cfg)["towers"]["fire"]["upgrade_damage_increase"].as<uint>();
				uint collateralDamageIncrease = (*cfg)["towers"]["fire"]["upgrade_collateral_damage_increase"].as<uint>();
				uint mult = (*cfg)["towers"]["fire"]["upgrade_damage_mult"].as<uint>();
				double base = (*cfg)["towers"]["fire"]["upgrade_damage_base"].as<double>();
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
				uint collateralRangeIncrease = (*cfg)["towers"]["fire"]["upgrade_collateral_range_increase"].as<uint>();
				uint mult = (*cfg)["towers"]["fire"]["upgrade_collateral_range_mult"].as<uint>();
				double base = (*cfg)["towers"]["fire"]["upgrade_collateral_range_base"].as<double>();
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
	vm.type = Fire;
	vm.xPos = _position->GetXPos();
	vm.yPos = _position->GetYPos();
	vm.experience = _experience;
	vm.level = _upgradeLevel;
	vm.range = _range;
	vm.projectile_ms_over_tile = _projectile_ms_over_tile;
	vm.nonFlyingDamage = -1;
	vm.collateral_damage = _collateralDamage;
	vm.collateral_range = _collateralRange;
	vm.slow_percent = -1;
	vm.slow_seconds = -1;
	vm.damage = _damage;

	uint damagemult = (*cfg)["towers"]["fire"]["upgrade_damage_mult"].as<uint>();
	uint rangemult = (*cfg)["towers"]["fire"]["upgrade_range_mult"].as<uint>();
	uint collateralrangemult = (*cfg)["towers"]["fire"]["upgrade_collateral_range_mult"].as<uint>();

	double damagebase = (*cfg)["towers"]["fire"]["upgrade_damage_base"].as<double>();
	double rangebase = (*cfg)["towers"]["fire"]["upgrade_range_base"].as<double>();
	double collatbase = (*cfg)["towers"]["fire"]["upgrade_collateral_range_base"].as<double>();
	vm.exp_required_for_damage_upgrade = floor(pow(damagebase, _upgradeLevel) * damagemult);
	vm.exp_required_for_range_upgrade = floor(pow(rangebase, _upgradeLevel) * rangemult);
	vm.exp_required_for_collateral_range_upgrade = floor(pow(collatbase, _upgradeLevel) * collateralrangemult);
	vm.exp_required_for_slow_upgrade = 0xFFFFFFFF;

	return vm;
}