#ifndef _PATH_TILE_
#define _PATH_TILE_

#include <unordered_set>
#include "ITile.h"
#include "IEnviormentUnit.h"

enum Direction { up, down, left, right };

class PathTile : public ITile {
private:
	Direction _direction;
	std::unordered_set<IEnviormentUnit*> _units;
public:
	PathTile(Direction dir);
	~PathTile();
	bool AcceptsStructures();
	bool IsPath();
	Direction GetDirection();
	char GetSymbol();
};

#endif
