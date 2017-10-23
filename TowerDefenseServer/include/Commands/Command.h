#ifndef _COMMAND_
#define _COMMAND_

#include "Map/Map.h"


class Command {
public:
	Command();
	virtual ~Command();
	virtual void Execute(Map* map) = 0;
};

#endif