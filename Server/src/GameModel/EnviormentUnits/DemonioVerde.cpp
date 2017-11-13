#include <iostream>

#include "../../../include/GameModel/EnviormentUnits/DemonioVerde.h"
#include "../../../include/GameModel/Map/PathTile.h"
#include "../../../include/GameModel/ViewModels/UnitVM.h"

DemonioVerde::DemonioVerde(uint id, uint stepDelay, uint healthPoints, ThreadSafeQueue<GameNotification*>& notifications)
 : EnviormentUnit(id, stepDelay, healthPoints, notifications) {}

DemonioVerde::~DemonioVerde()
{
	std::cout << "DemonioVerde" << GetId() << " IS DEAD!!!\n";
}

void DemonioVerde::PrintDebug(){
	PathTile* pos = GetPosition();
	if (pos == nullptr)
		std::cout << "DemonioVerde" << GetId() << " outside map\n";
	else
		std::cout << "DemonioVerde" << GetId() <<  "@(" << pos->GetXPos() << ", " << pos->GetYPos() << ")\n";
}

bool DemonioVerde::Flies(){
	return false;
}

UnitVM DemonioVerde::GetViewModel(){
	UnitVM vm;
	vm.unitType = UNIT_TYPE_DemonioVerde;
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