#include <memory>
#include <iostream>

#include "Towers/GroundTower.h"
#include "Map/SolidGroundTile.h"
#include "Commands/BuildTowerCommand.h"
#include "Towers/Tower.h"

BuildTowerCommand::BuildTowerCommand(TowerType type, unsigned int x, unsigned int y):
 _xPos(x), _yPos(y), _towerType(type) {}

BuildTowerCommand::~BuildTowerCommand(){}

void BuildTowerCommand::Execute(Map* map){
	switch(_towerType){
		case Ground: _BuildGroundTower(map);	break;
		case Air: _BuildAirTower(map);			break;
		case Ice: _BuildIceTower(map);			break;
		case Fire: _BuildFireTower(map);		break;
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

void BuildTowerCommand::_BuildFireTower(Map* map){

}
void BuildTowerCommand::_BuildIceTower(Map* map){

}
void BuildTowerCommand::_BuildAirTower(Map* map){

}