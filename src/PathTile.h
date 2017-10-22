#ifndef _PATH_TILE_
#define _PATH_TILE_

#include <vector>
#include "Tile.h"

class PathTile : public Tile {
private:
	PathTile* _next;
public:
	PathTile(unsigned int xPos, unsigned int yPos);
	~PathTile();
	char GetSymbol();
	PathTile* Next();
	void SetNextTile(PathTile* tile);
};

#endif
