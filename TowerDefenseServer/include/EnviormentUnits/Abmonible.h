#ifndef _ABMONIBLE_
#define _ABMONIBLE_

#include "EnviormentUnits/EnviormentUnit.h"
#include "Map/PathTile.h"

class Abmonible : public EnviormentUnit {
public:
	Abmonible(unsigned int id);
	~Abmonible();
	void PrintDebug();
	bool Flies();
};

#endif
