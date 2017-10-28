#ifndef _ESPECTRO_
#define _ESPECTRO_

#include "EnviormentUnits/EnviormentUnit.h"
#include "Map/PathTile.h"

class Espectro : public EnviormentUnit {
public:
	Espectro(uint id, uint stepDelay, uint healthPoints);
	~Espectro();
	void PrintDebug();
	bool Flies();
};

#endif
