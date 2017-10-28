#ifndef _HOMBRE_CABRA_
#define _HOMBRE_CABRA_

#include "EnviormentUnits/EnviormentUnit.h"
#include "Map/PathTile.h"

class HombreCabra : public EnviormentUnit {
public:
	HombreCabra(uint id, uint stepDelay, uint healthPoints);
	~HombreCabra();
	void PrintDebug();
	bool Flies();
};

#endif
