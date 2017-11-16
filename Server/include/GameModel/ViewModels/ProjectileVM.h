#ifndef _PROJECTILEVM_
#define _PROJECTILEVM_

#include "../../../../Common/Protocolo.h"

struct ProjectileVM {
  SPELL_TYPE type;
  uint flight_duration_ms;
  uint fromXpos;
  uint fromYpos;
  uint toXpos;
  uint toYpos;
};

#endif