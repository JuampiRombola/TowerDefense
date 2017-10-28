#include <iostream>


#include "Towers/Projectile.h"
#include "Map/SolidGroundTile.h"
#include "Exceptions/SolidGroundAlreadyHasTowerException.h"
#include "Towers/Tower.h"

SolidGroundTile::SolidGroundTile(uint xPos, uint yPos): 
Tile(xPos, yPos), _tower(nullptr) {}

SolidGroundTile::~SolidGroundTile()
{
	if (_tower != nullptr)
		delete _tower;
}

char SolidGroundTile::GetSymbol(){
	return 'L';
}

void SolidGroundTile::PlaceTower(Tower* t){
	if (t == nullptr)
		return;

	if (_tower == nullptr)
		_tower = t;
	else
		throw SolidGroundAlreadyHasTowerException();
}

Tower* SolidGroundTile::GetTower(){
	return _tower;
}

bool SolidGroundTile::HasTower(){
	return _tower != nullptr;
}

Projectile* SolidGroundTile::Step(){
	if (_tower != nullptr){
		return _tower->Step();
	}
	return nullptr;
}