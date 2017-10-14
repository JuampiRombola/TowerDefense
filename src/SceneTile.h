#ifndef _SCENE_TILE_
#define _SCENE_TILE_

#include "ITile.h"

class SceneTile : public ITile {
public:
	SceneTile();
	~SceneTile();
	bool AcceptsStructures();
	bool IsPath();
	char GetSymbol();
};

#endif
