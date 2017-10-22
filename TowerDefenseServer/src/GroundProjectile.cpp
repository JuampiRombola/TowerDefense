#include <iostream>

#include "GroundProjectile.h"
#include "Projectile.h"
#include "PathTile.h"

GroundProjectile::GroundProjectile(SolidGroundTile* origin, PathTile* target) :
 Projectile(origin, target, 10)
{

}

GroundProjectile::~GroundProjectile(){}

