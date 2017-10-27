
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
	SolidGroundTile* tile = map->GetSolidGroundTile(_xPos ,_yPos);
	if (tile != NULL && !tile->HasTower()){
		Tower* t = NULL;

		switch(_towerType){
			case Ground: 		t = _BuildGroundTower(map, tile);	break;
			case Wind: 			t = _BuildWindTower(map, tile);		break;
			case Ice: 			t = _BuildIceTower(map, tile);		break;
			case Fire: 			t = _BuildFireTower(map, tile);		break;
			default: break; // Lanzar excepcion
		}

		if (t != NULL)
			tile->PlaceTower(t);

		std::cout << "TOWER PLACED\n" << std::flush;

	}

}

Tower* BuildTowerCommand::_BuildGroundTower(Map* map, SolidGroundTile* tile){
	uint groundTowerCooldown = 2000;
	uint groundTowerRange = 200;
	return new GroundTower(groundTowerCooldown, groundTowerRange, 2, tile, map);
}

Tower* BuildTowerCommand::_BuildFireTower(Map* map, SolidGroundTile* tile){
	uint fireTowerDamage = 10;
	uint fireTowerCooldown = 2000;
	uint fireTowerRange = 5;
	uint collateralRange = 2;
	uint collateralDamage = 5;
	return new FireTower(fireTowerCooldown, fireTowerRange, fireTowerDamage, tile, map, collateralDamage, collateralRange);
}
Tower* BuildTowerCommand::_BuildIceTower(Map* map, SolidGroundTile* tile){
	uint iceTowerCooldown = 12000;
	uint iceTowerRange = 200;
	return new IceTower(iceTowerCooldown, iceTowerRange, 2, tile, map);
}
Tower* BuildTowerCommand::_BuildWindTower(Map* map, SolidGroundTile* tile){
	uint windTowerCooldown = 4000;
	uint windTowerRange = 200;
	return new WindTower(windTowerCooldown, windTowerRange, 2, tile, map);
}