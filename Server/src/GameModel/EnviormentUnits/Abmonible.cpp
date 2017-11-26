#include <iostream>
#include "../../../../Common/Protocolo.h"
#include "../../../include/GameModel/EnviormentUnits/Abmonible.h"
#include "../../../include/GameModel/Map/PathTile.h"
#include "../../../include/GameModel/ViewModels/UnitVM.h"

Abmonible::Abmonible(uint id, uint stepDelay, uint healthPoints, ThreadSafeQueue<GameNotification*>& notifications)
 : EnviormentUnit(id, stepDelay, healthPoints, notifications) {}

Abmonible::~Abmonible()
{
	std::cout << "Abmonible" << GetId() << " IS DEAD!!!\n";
}

void Abmonible::PrintDebug(){
	PathTile* pos = GetPosition();
	if (pos == nullptr)
		std::cout << "Abmonible" << GetId() << " outside map\n";
	else
		std::cout << "Abmonible" << GetId() <<  "@(" << pos->GetXPos() << ", " << pos->GetYPos() << ")\n";
}

bool Abmonible::Flies(){
	return false;
}

UnitVM Abmonible::GetViewModel(){
	UnitVM vm;
	vm.unitType = UNIT_TYPE_Abmonible;
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