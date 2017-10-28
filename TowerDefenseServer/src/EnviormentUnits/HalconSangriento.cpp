#include <iostream>

#include "EnviormentUnits/HalconSangriento.h"

HalconSangriento::HalconSangriento(uint id, uint stepDelay, uint healthPoints) : EnviormentUnit(id, stepDelay, healthPoints) {}

HalconSangriento::~HalconSangriento()
{
	std::cout << "HalconSangriento" << GetId() << " IS DEAD!!!\n";
}

void HalconSangriento::PrintDebug(){
	PathTile* pos = GetPosition();
	if (pos == nullptr)
		std::cout << "HalconSangriento" << GetId() << " outside map\n";
	else
		std::cout << "HalconSangriento" << GetId() <<  "@(" << pos->GetXPos() << ", " << pos->GetYPos() << ")\n";
}

bool HalconSangriento::Flies(){
	return true;
}