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
#include "../../../include/GameModel/ViewModels/CommandVM.h"
#include "../../../include/GameModel/GameNotifications/TowerPlacedGameNotification.h"


BuildTowerCommand::BuildTowerCommand(TowerType type, uint x, uint y):
 _xPos(x), _yPos(y), _towerType(type) {}

BuildTowerCommand::~BuildTowerCommand(){}

bool BuildTowerCommand::Execute(Map* map, TowerDefenseGame* game, ThreadSafeQueue<GameNotification*>& notifications){
	std::cout << "EXECUTINGG TOWER BUILD COMMAND\n" << std::flush;
	SolidGroundTile* tile = map->GetSolidGroundTile(_xPos ,_yPos);
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
			std::cout << "TOWER PLACED\n" << std::flush;
			TowerVM vm = t->GetViewModel();
			notifications.Queue(new TowerPlacedGameNotification(vm, game->GetPlayers()));
			return true;
		}
	}
	return false;
}

Tower* BuildTowerCommand::_BuildGroundTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg){
	uint cooldown_sec = cfg["towers"]["ground"]["cooldown_sec"].as<uint>();
	uint range = cfg["towers"]["ground"]["range"].as<uint>();
	uint damage = cfg["towers"]["ground"]["damage"].as<uint>();
	return new GroundTower(cooldown_sec * 1000, range, damage, tile, map);
}

Tower* BuildTowerCommand::_BuildFireTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg){
	uint damage = cfg["towers"]["fire"]["target_damage"].as<uint>();
	uint cooldown_sec = cfg["towers"]["fire"]["cooldown_sec"].as<uint>();
	uint range = cfg["towers"]["fire"]["range"].as<uint>();
	uint collateralRange = cfg["towers"]["fire"]["collateral_range"].as<uint>();
	uint collateralDamage = cfg["towers"]["fire"]["collateral_damage"].as<uint>();
	return new FireTower(cooldown_sec * 1000, range, damage, tile, map, collateralDamage, collateralRange);
}

Tower* BuildTowerCommand::_BuildWaterTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg){
	uint cooldown_sec = cfg["towers"]["water"]["cooldown_sec"].as<uint>();
	uint range = cfg["towers"]["water"]["range"].as<uint>();
	uint damage = cfg["towers"]["water"]["damage"].as<uint>();
	uint slowPercent = cfg["towers"]["water"]["slow_percent"].as<uint>();
	uint slowDuration_sec = cfg["towers"]["water"]["slow_duration_sec"].as<uint>();
	return new WaterTower(cooldown_sec * 1000, range, damage, slowPercent, slowDuration_sec, tile, map);
}

Tower* BuildTowerCommand::_BuildAirTower(Map* map, SolidGroundTile* tile, const YAML::Node& cfg){
	uint cooldown_sec = cfg["towers"]["air"]["cooldown_sec"].as<uint>();
	uint range = cfg["towers"]["air"]["range"].as<uint>();
	uint flyingTargetDamage = cfg["towers"]["air"]["flying_target_damage"].as<uint>();
	uint nonFlyingTargetDamage = cfg["towers"]["air"]["non_flying_target_damage"].as<uint>();
	return new AirTower(cooldown_sec * 1000, range, flyingTargetDamage, nonFlyingTargetDamage, tile, map);
}

CommandVM BuildTowerCommand::GetViewModel(){
	CommandVM vm;
	vm.type = BuildTower;
	vm.towerType = _towerType;
	vm.xPos = _xPos;
	vm.yPos = _yPos;
	return vm;
}