#include <memory>
#include <iostream>

#include "Towers/GroundTower.h"
#include "Towers/IceTower.h"
#include "Towers/WindTower.h"
#include "Towers/FireTower.h"
#include "Map/SolidGroundTile.h"
#include "Commands/BuildTowerCommand.h"
#include "Towers/Tower.h"

BuildTowerCommand::BuildTowerCommand(TowerType type, unsigned int x, unsigned int y):
 _xPos(x), _yPos(y), _towerType(type) {}

BuildTowerCommand::~BuildTowerCommand(){}

void BuildTowerCommand::Execute(Map* map){
	std::shared_ptr<SolidGroundTile> tile = map->GetSolidGroundTile(_xPos ,_yPos);
	if (tile.get() != nullptr && !tile.get()->HasTower()){
		std::shared_ptr<Tower> t;

		switch(_towerType){
			case Ground: 		t = _BuildGroundTower(map, tile);	break;
			case Wind: 			t = _BuildWindTower(map, tile);		break;
			case Ice: 			t = _BuildIceTower(map, tile);		break;
			case Fire: 			t = _BuildFireTower(map, tile);		break;
			default: break;
		}

		tile->PlaceTower(t);

		std::cout << "TOWER PLACED\n" << std::flush;

	}

}

std::shared_ptr<Tower> BuildTowerCommand::_BuildGroundTower(Map* map, std::shared_ptr<SolidGroundTile> tile){
	uint groundTowerCooldown = 2000;
	uint groundTowerRange = 200;
	return std::shared_ptr<GroundTower>(new GroundTower(groundTowerCooldown, groundTowerRange, 2, tile, map));
}

std::shared_ptr<Tower> BuildTowerCommand::_BuildFireTower(Map* map, std::shared_ptr<SolidGroundTile> tile){
	uint fireTowerCooldown = 2000;
	uint fireTowerRange = 200;
	return	std::shared_ptr<FireTower>(new FireTower(fireTowerCooldown, fireTowerRange, 2, tile, map));
}
std::shared_ptr<Tower> BuildTowerCommand::_BuildIceTower(Map* map, std::shared_ptr<SolidGroundTile> tile){
	uint iceTowerCooldown = 12000;
	uint iceTowerRange = 200;
	return std::shared_ptr<IceTower>(new IceTower(iceTowerCooldown, iceTowerRange, 2, tile, map));
}
std::shared_ptr<Tower> BuildTowerCommand::_BuildWindTower(Map* map, std::shared_ptr<SolidGroundTile> tile){
	uint windTowerCooldown = 6000;
	uint windTowerRange = 200;
	return std::shared_ptr<WindTower>(new WindTower(windTowerCooldown, windTowerRange, 2, tile, map));
}