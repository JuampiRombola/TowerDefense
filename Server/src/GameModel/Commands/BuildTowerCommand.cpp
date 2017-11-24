#include <iostream>

#include "../../../include/GameModel/Towers/GroundTower.h"
#include "../../../include/GameModel/Towers/WaterTower.h"
#include "../../../include/GameModel/Towers/AirTower.h"
#include "../../../include/GameModel/Towers/FireTower.h"
#include "../../../include/GameModel/Map/SolidGroundTile.h"
#include "../../../include/GameModel/Commands/BuildTowerCommand.h"
#include "../../../include/GameModel/Towers/Tower.h"
#include "../../../include/GameModel/TowerDefenseGame.h"
#include <yaml-cpp/yaml.h>
#include "../../../include/GameModel/GameNotifications/TowerPlacedGameNotification.h"
#include "../../../include/GameModel/GameNotifications/TowerUpgradedGameNotification.h"


BuildTowerCommand::BuildTowerCommand(TowerType type, uint x, uint y):
 _xPos(x), _yPos(y), _towerType(type) {}

BuildTowerCommand::~BuildTowerCommand(){}

bool BuildTowerCommand::Execute(Map* map, TowerDefenseGame* game, ThreadSafeQueue<GameNotification*>& notifications){
	std::cout << "EXECUTINGG TOWER BUILD COMMAND\n" << std::flush;
	SolidGroundTile* tile = map->GetSolidGroundTile(_xPos ,_yPos);
	_game = game;
	if (tile != nullptr && !tile->HasTower()){
		Tower* t = nullptr;

		switch(_towerType){
			case Ground:
				t = _BuildGroundTower(map, tile, game->GameCfg->Cfg);
				break;
			case Air:
				t = _BuildAirTower(map, tile, game->GameCfg->Cfg);
				break;
			case Water:
				t = _BuildWaterTower(map, tile, game->GameCfg->Cfg);
				break;
			case Fire:
				t = _BuildFireTower(map, tile, game->GameCfg->Cfg);
				break;
		}

		if (t != nullptr){
			tile->PlaceTower(t);
			TowerVM vm = t->GetViewModel();
			std::cout << "TOWER PLACED at " <<vm.xPos << ", " << vm.yPos << "\n" << std::flush;
			notifications.Queue(new TowerPlacedGameNotification(vm));
			notifications.Queue(new TowerUpgradedGameNotification(vm));
			return true;
		}
	}
	return false;
}

Tower* BuildTowerCommand::_BuildGroundTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg){
	uint cooldown_sec = cfg["towers"]["ground"]["cooldown_sec"].as<uint>();
	uint range = cfg["towers"]["ground"]["range"].as<uint>();
	uint damage = cfg["towers"]["ground"]["damage"].as<uint>();
	uint projectile_ms_over_tile = cfg["towers"]["ground"]["projectile_ms_over_tile"].as<uint>();
	GroundTower* t = new GroundTower(cooldown_sec * 1000, range, damage, tile, map, projectile_ms_over_tile, _game->notifications);
	t->cfg = &cfg;
}

Tower* BuildTowerCommand::_BuildFireTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg){
	uint damage = cfg["towers"]["fire"]["target_damage"].as<uint>();
	uint cooldown_sec = cfg["towers"]["fire"]["cooldown_sec"].as<uint>();
	uint range = cfg["towers"]["fire"]["range"].as<uint>();
	uint collateralRange = cfg["towers"]["fire"]["collateral_range"].as<uint>();
	uint collateralDamage = cfg["towers"]["fire"]["collateral_damage"].as<uint>();
	uint projectile_ms_over_tile = cfg["towers"]["fire"]["projectile_ms_over_tile"].as<uint>();
	FireTower* t = new FireTower(cooldown_sec * 1000, range, damage, tile, map, collateralDamage, collateralRange, projectile_ms_over_tile, _game->notifications);
	t->cfg = &cfg;
	return t;
}

Tower* BuildTowerCommand::_BuildWaterTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg){
	uint cooldown_sec = cfg["towers"]["water"]["cooldown_sec"].as<uint>();
	uint range = cfg["towers"]["water"]["range"].as<uint>();
	uint damage = cfg["towers"]["water"]["damage"].as<uint>();
	uint slowPercent = cfg["towers"]["water"]["slow_percent"].as<uint>();
	uint slowDuration_sec = cfg["towers"]["water"]["slow_duration_sec"].as<uint>();
	uint projectile_ms_over_tile = cfg["towers"]["water"]["projectile_ms_over_tile"].as<uint>();
	WaterTower* t = new WaterTower(cooldown_sec * 1000, range, damage, slowPercent, slowDuration_sec, tile, map, projectile_ms_over_tile, _game->notifications);
	t->cfg = &cfg;
	return t;
}

Tower* BuildTowerCommand::_BuildAirTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg){
	uint cooldown_sec = cfg["towers"]["air"]["cooldown_sec"].as<uint>();
	uint range = cfg["towers"]["air"]["range"].as<uint>();
	uint flyingTargetDamage = cfg["towers"]["air"]["flying_target_damage"].as<uint>();
	uint nonFlyingTargetDamage = cfg["towers"]["air"]["non_flying_target_damage"].as<uint>();
	uint projectile_ms_over_tile = cfg["towers"]["air"]["projectile_ms_over_tile"].as<uint>();
	AirTower* t = new AirTower(cooldown_sec * 1000, range, flyingTargetDamage, nonFlyingTargetDamage, tile, map, projectile_ms_over_tile, _game->notifications);
	t->cfg = &cfg;
	return t;
}
