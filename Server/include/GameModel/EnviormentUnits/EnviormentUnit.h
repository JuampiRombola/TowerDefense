#ifndef __ENVIORMENT_UNIT__
#define __ENVIORMENT_UNIT__

struct UnitVM;
class Map;
class PathTile;
#include "../GameNotifications/GameNotification.h"
#include "../../ThreadSafeQueue.h"


class EnviormentUnit{
protected:
	unsigned long long  _lastTimeStamp_ms;
	unsigned long long _lastSlowBeginTimeStamp_ms;
	unsigned long long _lastFreezeTimeStamp_ms;
	bool _alive;
	uint _id;
    uint _stepDelay_ms;
	int _healthPoints;

	PathTile* _position;
	PathTile* _lastPosition;

	Map* _map;

	bool _isSlowed;
	bool _isFrozen;
	uint _lastFreezeDuration_sec;
	uint _lastSlowDuration_sec;
	uint _activePercentSlow;

	ThreadSafeQueue<GameNotification*>& _notifications;
	std::vector<std::tuple<unsigned long long, uint, uint>> _slows;
	PathTile* _GetNextTile();
	uint _GetActualStepDelay();
	bool _CanStep();
public:
	EnviormentUnit(uint id, uint stepDelay_ms, int healthPoints, 
		ThreadSafeQueue<GameNotification*>& notifications);
	virtual ~EnviormentUnit();
	void Step();
	uint GetId();
	PathTile* GetPosition();
	void SetPosition(PathTile* pos, Map* map);
	void GetHit(uint hitPoints);
	virtual void PrintDebug() = 0;
	virtual bool Flies() = 0;
	bool IsAlive();
	uint GetHP();
	void PushBack();
	void Slow(uint slowSeconds, uint percentSlow);
	bool IsSlowed();
	void Kill();
	void Freeze(uint seconds);
	virtual UnitVM GetViewModel() = 0;
	bool deathNotified;
};

#endif
