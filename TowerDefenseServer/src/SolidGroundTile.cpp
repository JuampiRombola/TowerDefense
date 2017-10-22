#include <iostream>

#include "SolidGroundTile.h"
#include "SolidGroundAlreadyHasTowerException.h"

SolidGroundTile::SolidGroundTile(unsigned int xPos, unsigned int yPos) : Tile(xPos, yPos) {}

SolidGroundTile::~SolidGroundTile(){}

char SolidGroundTile::GetSymbol(){
	return 'L';
}

void SolidGroundTile::PlaceTower(Tower* tower){
	if (_tower == NULL)
		_tower = tower;
	else
		throw new SolidGroundAlreadyHasTowerException();
}

bool SolidGroundTile::HasTower(){
	return _tower != NULL;
}