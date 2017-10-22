#ifndef __ENVIORMENT_UNIT__
#define __ENVIORMENT_UNIT__

class Map;
class PathTile;

class EnviormentUnit{
private:
	uint _id;
	uint _speed;
	uint _movementTimer;

	PathTile* _position;
	PathTile* _lastPosition;

	Map* _map;
public:
	EnviormentUnit(uint id, uint speed);
	virtual ~EnviormentUnit();
	void Step();
	unsigned int GetId();
	PathTile* GetPosition();
	void SetPosition(PathTile* pos, Map* map);
	virtual void PrintDebug() = 0;
};

#endif
