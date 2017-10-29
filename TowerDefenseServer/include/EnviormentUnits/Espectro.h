#ifndef _ESPECTRO_
#define _ESPECTRO_

#include "EnviormentUnits/EnviormentUnit.h"
struct UnitVM;


class Espectro : public EnviormentUnit {
public:
	Espectro(uint id, uint stepDelay, uint healthPoints);
	~Espectro();
	void PrintDebug();
	bool Flies();
	UnitVM GetViewModel();
};

#endif
