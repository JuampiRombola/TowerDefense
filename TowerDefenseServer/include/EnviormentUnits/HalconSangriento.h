#ifndef _HALCON_SANGRIENTO_
#define _HALCON_SANGRIENTO_

#include "EnviormentUnits/EnviormentUnit.h"

class HalconSangriento : public EnviormentUnit {
public:
	HalconSangriento(uint id, uint stepDelay, uint healthPoints);
	~HalconSangriento();
	void PrintDebug();
	bool Flies();
	UnitVM GetViewModel();
};

#endif
