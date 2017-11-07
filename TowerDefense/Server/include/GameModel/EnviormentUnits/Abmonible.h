#ifndef _ABMONIBLE_
#define _ABMONIBLE_

#include "../EnviormentUnits/EnviormentUnit.h"

class UnitVM;

class Abmonible : public EnviormentUnit {
public:
	Abmonible(uint id, uint stepDelay, uint healthPoints, ThreadSafeQueue<GameNotification*>& notifications);
	~Abmonible();
	void PrintDebug();
	bool Flies();
	UnitVM GetViewModel();
};

#endif
