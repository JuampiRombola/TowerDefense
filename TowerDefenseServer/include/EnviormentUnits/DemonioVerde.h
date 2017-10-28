#ifndef _DEMONIO_VERDE_
#define _DEMONIO_VERDE_

#include "EnviormentUnits/EnviormentUnit.h"
#include "Map/PathTile.h"

class DemonioVerde : public EnviormentUnit {
public:
	DemonioVerde(uint id, uint stepDelay, uint healthPoints);
	~DemonioVerde();
	void PrintDebug();
	bool Flies();
};

#endif
