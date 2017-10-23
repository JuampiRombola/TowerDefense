#ifndef __ENVIORMENT_UNIT__
#define __ENVIORMENT_UNIT__

#include <memory>

class Map;
class PathTile;

class EnviormentUnit{
private:
	unsigned long long _lastTimeStamp_ms;
	bool _alive;
	uint _id;
	uint _speed;
	uint _healthPoints;

	std::shared_ptr<PathTile> _position;
	std::shared_ptr<PathTile> _lastPosition;

	Map* _map;

	std::shared_ptr<PathTile> _GetNextTile();
	bool _CanStep();
public:
	EnviormentUnit(uint id, uint speed, uint healthPoints);
	virtual ~EnviormentUnit();
	void Step(std::shared_ptr<EnviormentUnit> thisUnit);
	unsigned int GetId();
	std::shared_ptr<PathTile> GetPosition();
	void SetPosition(std::shared_ptr<PathTile> pos, Map* map);
	void GetHit(uint hitPoints);
	virtual void PrintDebug() = 0;
	virtual bool Flies() = 0;
	bool IsAlive();
};

#endif
