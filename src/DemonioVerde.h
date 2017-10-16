#ifndef _DEMONIO_VERDE_
#define _DEMONIO_VERDE_

#include "EnviormentUnit.h"
#include "PathTile.h"

class DemonioVerde : public EnviormentUnit {
public:
	DemonioVerde(unsigned int id);
	~DemonioVerde();
	void PrintDebug();
};

#endif
