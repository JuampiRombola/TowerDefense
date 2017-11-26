#include <iostream>

#include "../../../include/GameModel/EnviormentUnits/NoMuerto.h"
#include "../../../include/GameModel/Map/PathTile.h"
#include "../../../include/GameModel/ViewModels/UnitVM.h"

NoMuerto::NoMuerto(uint id, uint stepDelay, uint healthPoints, ThreadSafeQueue<GameNotification*>& notifications) 
: EnviormentUnit(id, stepDelay, healthPoints, notifications) {}

NoMuerto::~NoMuerto()
{
	std::cout << "NoMuerto" << GetId() << " IS DEAD!!!\n";
}

void NoMuerto::PrintDebug(){
	PathTile* pos = GetPosition();
	if (pos == nullptr)
		std::cout << "NoMuerto" << GetId() << " outside map\n";
	else
		std::cout << "NoMuerto" << GetId() <<  "@(" << pos->GetXPos() << ", " << pos->GetYPos() << ")\n";
}

bool NoMuerto::Flies(){
	return false;
}

UnitVM NoMuerto::GetViewModel(){
	UnitVM vm;
	vm.unitType = UNIT_TYPE_NoMuerto;
	vm.healthPoints = _healthPoints;
	vm.xPos = (_position != nullptr) ? _position->GetXPos() : -1;
	vm.yPos = (_position != nullptr) ? _position->GetYPos() : -1;
	if (_position != nullptr && _position->next != nullptr){
		vm.nextXpos = _position->next->GetXPos();
		vm.nextYpos = _position->next->GetYPos();
	} else{
		vm.nextYpos = -1;
		vm.nextXpos = -1;
	}
	vm.stepDelay_ms = _stepDelay_ms;
	vm.id = _id;
	return vm;
}