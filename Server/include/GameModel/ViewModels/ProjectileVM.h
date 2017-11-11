#ifndef _PROJECTILEVM_
#define _PROJECTILEVM_

enum ProjectileType { pFire, pWater, pAir, pGround }; 

struct ProjectileVM {
  ProjectileType type;
  uint distanceToCover;
  uint distanceCovered;
  uint fromXpos;
  uint fromYpos;
  uint toXpos;
  uint toYpos;
};

#endif