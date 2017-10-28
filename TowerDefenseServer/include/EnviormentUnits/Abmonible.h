#ifndef _ABMONIBLE_
#define _ABMONIBLE_

#include "EnviormentUnits/EnviormentUnit.h"
#include "Map/PathTile.h"

class Abmonible : public EnviormentUnit {
public:
	Abmonible(uint id, uint stepDelay, uint healthPoints);
	~Abmonible();
	void PrintDebug();
	bool Flies();
};

#endif
