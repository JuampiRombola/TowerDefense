#include <iostream>


#include "Towers/Projectile.h"
#include "Map/SolidGroundTile.h"
#include "Exceptions/SolidGroundAlreadyHasTowerException.h"
#include "Towers/Tower.h"

SolidGroundTile::SolidGroundTile(unsigned int xPos, unsigned int yPos): 
Tile(xPos, yPos), _tower(NULL) {}

SolidGroundTile::~SolidGroundTile()
{
	if (_tower != NULL)
		delete _tower;
}

char SolidGroundTile::GetSymbol(){
	return 'L';
}

void SolidGroundTile::PlaceTower(Tower* t){
	if (t == NULL)
		return;

	if (_tower == NULL)
		_tower = t;
	else
		throw new SolidGroundAlreadyHasTowerException();
}

bool SolidGroundTile::HasTower(){
	return _tower != nullptr;
}

Projectile* SolidGroundTile::Step(){
	if (_tower != nullptr){
		return _tower->Step();
	}
	return NULL;
}