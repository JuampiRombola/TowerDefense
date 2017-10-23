#ifndef _NO_MUERTO_
#define _NO_MUERTO_

#include "EnviormentUnits/EnviormentUnit.h"
#include "Map/PathTile.h"

class NoMuerto : public EnviormentUnit {
public:
	NoMuerto(unsigned int id);
	~NoMuerto();
	void PrintDebug();
	bool Flies();
};

#endif
