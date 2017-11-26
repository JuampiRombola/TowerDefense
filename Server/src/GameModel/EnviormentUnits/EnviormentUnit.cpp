#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

#include "../../../include/GameModel/GameNotifications/UnitPositionGameNotification.h"

#include "../../../include/GameModel/Map/Map.h"
#include "../../../include/GameModel/Map/PathTile.h"
#include "../../../include/GameModel/EnviormentUnits/EnviormentUnit.h"
#include "../../../include/GameModel/Helpers.h"
#include "../../../include/GameModel/Exceptions/NonPlacedUnitCannotStepException.h"
#include "../../../include/GameModel/Exceptions/IncompletePathException.h"
#include "../../../include/GameModel/GameNotifications/UnitSpeedUpdateGameNotification.h"

EnviormentUnit::EnviormentUnit(uint id, uint stepDelay_ms, int healthpoints,
							   ThreadSafeQueue<GameNotification*>& notifications):
_lastTimeStamp_ms(0), _lastSlowBeginTimeStamp_ms(0), _lastFreezeTimeStamp_ms(0),
 _alive(true), _id(id), _stepDelay_ms(stepDelay_ms),
 _healthPoints(healthpoints), _position(nullptr), _lastPosition(nullptr), 
_map(nullptr), _isSlowed(false), _isFrozen(false), _lastFreezeDuration_sec(0),
 _lastSlowDuration_sec(0), _activePercentSlow(1), _notifications(notifications), _slows(), deathNotified(false)
{
	std::cout << "Env unit created base delay "  << _stepDelay_ms << std::endl;
}

EnviormentUnit::~EnviormentUnit(){
}

void EnviormentUnit::Kill(){
	_healthPoints = 0;
	_alive = false;
}

uint EnviormentUnit::GetHP(){
	return _healthPoints;
}

void EnviormentUnit::PushBack(){
	if (_lastPosition == nullptr)
		return;

	_position->UnitLeave(this); 
	_lastPosition->UnitEnter(this);

	_position = _lastPosition;
	_lastPosition = nullptr;
	std::cout << "EnviormentUnit Pushed backed\n" << std::flush;
	PrintDebug();
}


void EnviormentUnit::Freeze(uint seconds){
	_isFrozen = true;
	_lastFreezeTimeStamp_ms = Helpers::MillisecondsTimeStamp();
	_lastFreezeDuration_sec = seconds;
	std::cout << "EnviormentUnit frozen for " << seconds << "\n";
}

void EnviormentUnit::GetHit(uint hitpoints){
	_healthPoints -= hitpoints;
	std::cout << "EnviormentUnit" << _id << " GOT HIT for " << hitpoints 
	<< "hp, now has " << _healthPoints << "hp\n" << std::flush;
	if (_healthPoints <= 0)
		_alive = false;
}

bool EnviormentUnit::IsAlive(){
	return _alive;
}


void EnviormentUnit::Slow(uint slowSeconds, uint percentSlow){
	auto ts = Helpers::MillisecondsTimeStamp();
    uint delayIncrement = floor((_stepDelay_ms / (double) 100) * (double) percentSlow);
	_stepDelay_ms += delayIncrement;
	
	std::cout << "slow started: unit _stepDelay_ms now is: " << _stepDelay_ms << std::endl << std::flush;
    auto tup = std::tuple<unsigned long long, uint, uint>(ts, (slowSeconds * 1000), delayIncrement);
	_slows.push_back(tup);
	_notifications.Queue(new UnitSpeedUpdateGameNotification(_id, _stepDelay_ms));
/*	_isSlowed = true;
	_activePercentSlow = percentSlow;
	_lastSlowBeginTimeStamp_ms = Helpers::MillisecondsTimeStamp();
	_lastSlowDuration_sec = slowSeconds;*/
}


void EnviormentUnit::Step(){
	if (!_alive || !_CanStep())
		return;

	PathTile* next = _GetNextTile();

	if (next == nullptr){
		throw IncompletePathException();
	}

	_position->UnitLeave(this); 
	next->UnitEnter(this);

	_lastPosition = _position;
	_position = next;

	UnitVM vm = GetViewModel();
	_notifications.Queue(new UnitPositionGameNotification(vm));
	PrintDebug();
}


bool EnviormentUnit::_CanStep(){
	if (!IsAlive())
		return false;

	if (_position == nullptr || _map == nullptr)
		throw NonPlacedUnitCannotStepException();

    unsigned long long ts = Helpers::MillisecondsTimeStamp();

	if (_isFrozen){
		uint delta = ts - _lastFreezeTimeStamp_ms;
		if (delta > _lastFreezeDuration_sec * 1000){
			_isFrozen = false;
			_lastFreezeDuration_sec = 0;
			_lastFreezeTimeStamp_ms = 0;
		} else {
			return false;
		}
	}

	if (_lastTimeStamp_ms == 0){
		_lastTimeStamp_ms = Helpers::MillisecondsTimeStamp();
		return true;
	}

    for (auto it = _slows.begin(); it != _slows.end();){
        auto tup = *it;
        auto slowTsBegin = std::get<0>(tup);
        uint slowDuration_ms = std::get<1>(tup);
        uint delayIncrement_ms = std::get<2>(tup);
        if (ts - slowTsBegin > slowDuration_ms){
            _stepDelay_ms -= delayIncrement_ms;
            std::cout << "slow endend: unit _stepDelay_ms now is: " << _stepDelay_ms << std::endl << std::flush;
			_notifications.Queue(new UnitSpeedUpdateGameNotification(_id, _stepDelay_ms));
			it = _slows.erase(it);
        } else {
            ++it;
        }
    }



	uint delta = ts - _lastTimeStamp_ms;

	if (delta > _stepDelay_ms){
		_lastTimeStamp_ms = ts;
		return true;
	}

	return false;
}

bool EnviormentUnit::IsSlowed(){
	return _isSlowed;
}

uint EnviormentUnit::_GetActualStepDelay(){
/*
	if (IsSlowed()){
		unsigned long long ts = Helpers::MillisecondsTimeStamp();
		unsigned long long delta_ms = ts - _lastSlowBeginTimeStamp_ms;
		unsigned long long dur_ms = _lastSlowDuration_sec * 1000;

		if ( delta_ms > dur_ms ){
			_isSlowed = false;
			return _speedtiles_over_second;
		}

		double increasedDelay = _speedtiles_over_second * ((((double) _activePercentSlow ) / 100) + 1);
		return increasedDelay;
	} 
	return _speedtiles_over_second;*/
    return 0;
}

PathTile* EnviormentUnit::_GetNextTile(){

	return _position->next;

/*
	std::vector<PathTile*> p = _position->GetPossibleNextTiles(_lastPosition);

	if (p.begin() == p.end()){
		std::vector<PathTile*> possiblePaths;
		int x = _position->GetXPos();
		int y = _position->GetYPos();
		PathTile* up = _map->GetPathTile(x, y+1);
		PathTile* down = _map->GetPathTile(x, y-1);
		PathTile* right = _map->GetPathTile(x+1, y);
		PathTile* left = _map->GetPathTile(x-1, y);
		if (up != nullptr)	possiblePaths.push_back(up);
		if (down != nullptr) possiblePaths.push_back(down);
		if (right != nullptr) possiblePaths.push_back(right);
		if (left != nullptr) possiblePaths.push_back(left);
		std::srand(std::time(0));

		if (possiblePaths.size() > 0)
			return possiblePaths[random_variable];
		return nullptr;
	} 
	else
	{
		std::srand(std::time(0));
		uint random_variable = (uint) std::rand() % p.size();
		return p[random_variable];
	}*/
}

PathTile* EnviormentUnit::GetPosition(){
	return _position;
}

void EnviormentUnit::SetPosition(PathTile* pos, Map* map){
	_position = pos;
	_map = map;
}
uint EnviormentUnit::GetId(){
	return _id;
}

