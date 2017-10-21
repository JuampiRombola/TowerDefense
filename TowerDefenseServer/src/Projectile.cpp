#include <iostream>

#include "Projectile.h"
#include "PathTile.h"

Projectile::Projectile(PathTile* target, uint speed) :
_target(target), _speed(speed), _impacted(false)
{

}

Projectile::~Projectile(){}


void Projectile::Step(){

}

void Projectile::PrintDebug(){
	
}

bool Projectile::Impacted(){
	return _impacted;
}