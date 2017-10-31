#ifndef _NO_MUERTO_
#define _NO_MUERTO_

#include "../EnviormentUnits/EnviormentUnit.h"
struct UnitVM;

class NoMuerto : public EnviormentUnit {
public:
	NoMuerto(uint id, uint stepDelay, uint healthPoints);
	~NoMuerto();
	void PrintDebug();
	bool Flies();
	UnitVM GetViewModel();
};

#endif
