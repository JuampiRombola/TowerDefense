#include <iostream>

#include "../../include/EnviormentUnits/HalconSangriento.h"
#include "../../include/Map/PathTile.h"
#include "../../include/ViewModels/UnitVM.h"

HalconSangriento::HalconSangriento(uint id, uint stepDelay, uint healthPoints, ThreadSafeQueue<GameNotification*>& notifications)
 : EnviormentUnit(id, stepDelay, healthPoints, notifications) {}

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
	if (_position->next != nullptr){
		vm.nextXpos = _position->next->GetXPos();
		vm.nextYpos = _position->next->GetYPos();
	} else{
		vm.nextYpos = -1;
		vm.nextXpos = -1;
	}
	vm.stepDelay_ms = _GetActualStepDelay();
	vm.id = _id;
	return vm;
}