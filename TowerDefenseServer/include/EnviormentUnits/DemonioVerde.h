#ifndef _DEMONIO_VERDE_
#define _DEMONIO_VERDE_

#include "EnviormentUnits/EnviormentUnit.h"
#include "Map/PathTile.h"

class DemonioVerde : public EnviormentUnit {
public:
	DemonioVerde(unsigned int id);
	~DemonioVerde();
	void PrintDebug();
	bool Flies();
};

#endif
