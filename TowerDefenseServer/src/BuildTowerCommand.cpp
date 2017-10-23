#include <memory>
#include <iostream>

#include "GroundTower.h"
#include "BuildTowerCommand.h"
#include "Tower.h"

BuildTowerCommand::BuildTowerCommand(TowerType type, unsigned int x, unsigned int y):
 _xPos(x), _yPos(y), _towerType(type) {}

BuildTowerCommand::~BuildTowerCommand(){}

void BuildTowerCommand::Execute(Map* map){
	switch(_towerType){
		case Ground: _BuildGroundTower(map);	break;
		case Air: _BuildAirTower();			break;
		case Ice: _BuildIceTower();			break;
		case Fire: _BuildFireTower();		break;
		default: break;
	}
}

void BuildTowerCommand::_BuildGroundTower(Map* map){
	uint GROUNDTOWERCOOLDOWN = 2000;
	uint GROUNDTOWERRANGE = 200;

	std::shared_ptr<SolidGroundTile> tile = map->GetSolidGroundTile(_xPos ,_yPos);
	if (tile.get() != nullptr && !tile.get()->HasTower()){
		std::shared_ptr<Tower> t = std::shared_ptr<GroundTower>
			(new GroundTower(GROUNDTOWERCOOLDOWN, GROUNDTOWERRANGE, tile, map));
		tile->PlaceTower(t);
		std::cout << "TOWER PLACED\n" << std::flush;
	}
}

void BuildTowerCommand::_BuildFireTower(){

}
void BuildTowerCommand::_BuildIceTower(){

}
void BuildTowerCommand::_BuildAirTower(){

}