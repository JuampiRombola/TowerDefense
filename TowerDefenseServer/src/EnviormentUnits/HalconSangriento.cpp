#include <iostream>

#include "EnviormentUnits/HalconSangriento.h"
#include "Map/PathTile.h"
#include "ViewModels/UnitVM.h"

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

UnitVM HalconSangriento::GetViewModel(){
	UnitVM vm;
	vm.unitType = uHalconSangriento;
	vm.healthPoints = _healthPoints;
	vm.xPos = _position->GetXPos();
	vm.yPos = _position->GetYPos();
	vm.stepDelay_ms = _GetActualStepDelay();
	vm.id = _id;
	return vm;
}