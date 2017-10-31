#ifndef _DEMONIO_VERDE_
#define _DEMONIO_VERDE_

#include "../EnviormentUnits/EnviormentUnit.h"
struct UnitVM;


class DemonioVerde : public EnviormentUnit {
public:
	DemonioVerde(uint id, uint stepDelay, uint healthPoints);
	~DemonioVerde();
	void PrintDebug();
	bool Flies();
	UnitVM GetViewModel();
};

#endif
