#ifndef _STRUCTURE_TILE_
#define _STRUCTURE_TILE_

#include "ITile.h"


class StructureTile : public ITile {
public:
	StructureTile();
	~StructureTile();
	bool AcceptsStructures();
	bool IsPath();
	char GetSymbol();
};

#endif
