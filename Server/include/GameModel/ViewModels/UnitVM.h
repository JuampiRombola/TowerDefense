#ifndef _UNITVM_
#define _UNITVM_

#include "../../../../Common/Protocolo.h"

struct UnitVM {
    UNIT_TYPE unitType;
  int healthPoints;
  unsigned int xPos;
  unsigned int yPos;
  unsigned int nextXpos;
  unsigned int nextYpos;
  unsigned int stepDelay_ms;
  unsigned int id;
};

#endif