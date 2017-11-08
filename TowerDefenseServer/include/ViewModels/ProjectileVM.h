#ifndef _PROJECTILEVM_
#define _PROJECTILEVM_

enum ProjectileType { pFire, pWater, pAir, pGround }; 

struct ProjectileVM {
  ProjectileType type;
    unsigned int distanceToCover;
    unsigned int distanceCovered;
    unsigned int fromXpos;
    unsigned int fromYpos;
    unsigned int toXpos;
    unsigned int toYpos;
};

#endif