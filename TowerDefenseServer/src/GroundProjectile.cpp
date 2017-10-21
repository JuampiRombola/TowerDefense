#include <iostream>

#include "GroundProjectile.h"
#include "Projectile.h"
#include "PathTile.h"

GroundProjectile::GroundProjectile(PathTile* target) :
 Projectile(target,10)
{

}

GroundProjectile::~GroundProjectile(){}

