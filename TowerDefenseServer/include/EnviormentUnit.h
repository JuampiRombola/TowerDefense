#ifndef __ENVIORMENT_UNIT__
#define __ENVIORMENT_UNIT__

class Map;
class PathTile;

class EnviormentUnit{
private:
	unsigned int _id;
	PathTile* _position;
	PathTile* _lastPosition;

	Map* _map;
public:
	EnviormentUnit(unsigned int id);
	virtual ~EnviormentUnit();
	void Step();
	unsigned int GetId();
	PathTile* GetPosition();
	void SetPosition(PathTile* pos, Map* map);
	virtual void PrintDebug() = 0;
};

#endif
