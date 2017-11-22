#include <iostream>
#include <algorithm>
#include <ctime>
#include <map>

#include "../../../include/GameModel/Map/Map.h"
#include "../../../include/GameModel/Exceptions/UnitIsNotOnThisTileException.h"
#include "../../../include/GameModel/Exceptions/UnitIsAlreadyOnThisTileException.h"
#include "../../../include/GameModel/Exceptions/IncompletePathException.h"

#include "../../../include/GameModel/EnviormentUnits/EnviormentUnit.h"
#include "../../../include/GameModel/Helpers.h"
#include "../../../include/GameModel/Map/PathTile.h"

PathTile::PathTile(uint xPos, uint yPos, Map* map, PathTile* next) 
: Tile(xPos, yPos), _lastCrackTimeStamp_ms(0), _lastFireTimeStamp_ms(0), _lastVentiscaTimeStamp_ms(0),
_lastTornadoTimeStamp_ms(0), _lastCrackDuration_ms(0), _lastFireDuration_ms(0), _lastVentiscaDuration_ms(0), 
 _lastFireDamage(0), _lastVentiscaDamage(0), 
 _lastVentiscaSlowPercent(0), _lastVentiscaSlowDuration_ms(0), _lastTornadoDuration_ms(0), _lastTornadoMaxDamage(0), 
_isCracked(false), _isOnFire(false), _hasVentisca(false), _hasTornado(false), _canSpawn(false), _units(), 
_possibleNextPaths(), _map(map), next(next) {}


PathTile::~PathTile(){}


char PathTile::GetSymbol(){
	return 'P';
}

void PathTile::Crack(uint time_ms){
	_isCracked = true;
	_lastCrackTimeStamp_ms = Helpers::MillisecondsTimeStamp();
	_lastCrackDuration_ms = time_ms;
}

void PathTile::SetOnFire(uint time_ms, uint fireDamage){
	_isOnFire = true;
	_lastFireTimeStamp_ms = Helpers::MillisecondsTimeStamp();
	_lastFireDuration_ms = time_ms;
	_lastFireDamage = fireDamage;
	for (auto it = _units.begin(); it != _units.end(); ++it){
		(*it)->GetHit(_lastFireDamage);
	}
}

void PathTile::Ventisca(uint ventiscaDamage, uint ventiscaDuration_sec, uint slowDuration_sec, uint percentSlow){
	_hasVentisca = true;
	_lastVentiscaDamage = ventiscaDamage;
	_lastVentiscaSlowPercent = percentSlow;
	_lastVentiscaSlowDuration_ms = slowDuration_sec * 1000;
	_lastVentiscaDuration_ms = ventiscaDuration_sec * 1000;
	_lastVentiscaTimeStamp_ms = Helpers::MillisecondsTimeStamp();
	for (auto it = _units.begin(); it != _units.end(); ++it){
		(*it)->GetHit(_lastVentiscaDamage);
		(*it)->Slow(_lastVentiscaDuration_ms / 1000, _lastVentiscaSlowPercent);
	}
}

void PathTile::Tornado(uint tornadoMaxDamage, uint tornadoDuration_sec){
	_hasTornado = true;
	_lastTornadoMaxDamage = tornadoMaxDamage;
	_lastTornadoDuration_ms = tornadoDuration_sec * 1000;
	_lastTornadoTimeStamp_ms = Helpers::MillisecondsTimeStamp();
	for (auto it = _units.begin(); it != _units.end(); ++it){
		std::srand(std::time(0));
		uint randomDamage = (uint) std::rand() % _lastTornadoMaxDamage;
		(*it)->GetHit(randomDamage);
	}
}

Map* PathTile::GetMap(){
	return _map;
}

void PathTile::InitPossiblePaths(){
	PathTile* up = _map->GetPathTile(GetXPos(), GetYPos() + 1);
	PathTile* down = _map->GetPathTile(GetXPos(), GetYPos() - 1);
	PathTile* left = _map->GetPathTile(GetXPos() - 1, GetYPos());
	PathTile* right = _map->GetPathTile(GetXPos() + 1, GetYPos());
	
	int a = 0;
	if (GetXPos() == 8 && GetYPos() == 4){
		a++;
	}
	if (a);


	if (up != nullptr){
		try
		{
			if (!up->DrivesStraightToSpawnFrom(this)){

				if (down != nullptr)
					_possibleNextPaths[down].push_back(up);

				if (left != nullptr)
					_possibleNextPaths[left].push_back(up);

				if (right != nullptr)
					_possibleNextPaths[right].push_back(up);
			}
		} catch (std::exception& e) { /* */ }

	}

	if (down != nullptr){
		try
		{
			if (!down->DrivesStraightToSpawnFrom(this)){

				if (up != nullptr)
					_possibleNextPaths[up].push_back(down);

				if (left != nullptr)
					_possibleNextPaths[left].push_back(down);

				if (right != nullptr)
					_possibleNextPaths[right].push_back(down);
			}
		} catch (std::exception& e) { /* */ }
	}

	if (right != nullptr){
		try
		{
			if (!right->DrivesStraightToSpawnFrom(this)){

				if (up != nullptr)
					_possibleNextPaths[up].push_back(right);

				if (left != nullptr)
					_possibleNextPaths[left].push_back(right);

				if (down != nullptr)
					_possibleNextPaths[down].push_back(right);
			}
		} catch (std::exception& e) { /* */ }
	}

	if (left != nullptr){
		try
		{
			if (!left->DrivesStraightToSpawnFrom(this)){

				if (up != nullptr)
					_possibleNextPaths[up].push_back(left);

				if (right != nullptr)
					_possibleNextPaths[right].push_back(left);

				if (down != nullptr)
					_possibleNextPaths[down].push_back(left);
			}
		} catch (std::exception& e) { /* */ }
	}
}


bool PathTile::CanSpawn(){
	return _canSpawn;
}

void PathTile::SetCanSpawn(){
	_canSpawn = true;
}


void PathTile::UnitEnter(EnviormentUnit* unit){
	auto it = std::find(_units.begin(), _units.end(), unit);
	if (it == _units.end())
		_units.emplace_back(unit);
	else 
		throw UnitIsAlreadyOnThisTileException();

	unsigned long long ts_ms = Helpers::MillisecondsTimeStamp();
	if (_isCracked && !unit->Flies()){
		uint delta_ms = ts_ms - _lastCrackTimeStamp_ms;
		if (delta_ms > _lastCrackDuration_ms){
			_isCracked = false;
			_lastCrackDuration_ms = 0;
		} else {
			std::cout << "FALLED INTO CRACK\n" << std::flush;
			unit->Kill();
			return;
		}
	}

	if (_isOnFire){
		uint delta_ms = ts_ms - _lastFireTimeStamp_ms;
		if (delta_ms > _lastFireDuration_ms){
			_isOnFire = false;
			_lastFireDuration_ms = 0;
		} else {
			std::cout << "UNIT GOT BURNT!!\n" << std::flush;
			unit->GetHit(_lastFireDamage);
		}
	}

	if (_hasVentisca){
		uint delta_ms = ts_ms - _lastVentiscaTimeStamp_ms;
		if (delta_ms > _lastVentiscaDuration_ms){
			_hasVentisca = false;
			_lastVentiscaDuration_ms = 0;
			_lastVentiscaSlowPercent = 0;
			_lastVentiscaSlowPercent = 0;
			_lastVentiscaDamage = 0;
		} else {
			unit->GetHit(_lastVentiscaDamage);
			unit->Slow(_lastVentiscaSlowDuration_ms / 1000, _lastVentiscaSlowPercent); 
		}
	}

	if (_hasTornado){
		uint delta_ms = ts_ms - _lastTornadoTimeStamp_ms;
		if (delta_ms > _lastTornadoDuration_ms){
			_hasTornado = false;
			_lastTornadoDuration_ms = 0;
			_lastTornadoMaxDamage = 0;
		} else {
			std::srand(std::time(0));
			uint randomDamage = (uint) std::rand() % _lastTornadoMaxDamage;
			unit->GetHit(randomDamage); 
		}
	}
}


void PathTile::UnitLeave(EnviormentUnit* unit){

	auto it = std::find(_units.begin(), _units.end(), unit);
	if (it != _units.end()){
		_units.erase(it);
		unit->SetPosition(nullptr, _map); 
	}
	else
		throw UnitIsNotOnThisTileException();
}

bool PathTile::HasAnyUnit(){
	return _units.begin() != _units.end();
}

std::vector<EnviormentUnit*> PathTile::GetUnits(){ //copia!!!!!
	return _units;
}

std::vector<PathTile*> PathTile::GetPossibleNextTiles(PathTile* from){
	if (from == nullptr)
		return std::vector<PathTile*>();
	return _possibleNextPaths[from];
}

bool PathTile::DrivesStraightToSpawnFrom(PathTile* tile){

	uint fromX = tile->GetXPos();
	uint fromY = tile->GetYPos();
	uint x = this->GetXPos();
	uint y = this->GetYPos();

	PathTile* front;
	PathTile* side1;
	PathTile* side2;

	std::vector<PathTile*> endTiles = _map->GetFinishTiles();
	std::vector<PathTile*> paths;

	while (true){
		paths.clear();
		if (fromX == x){
			uint dif = fromY - y;
			front = _map->GetPathTile(x, y - dif);
			side1 = _map->GetPathTile(x + 1, y);
			side2 = _map->GetPathTile(x - 1, y);
		} else if (fromY == y){
			uint dif = fromX - x;
			front = _map->GetPathTile(x - dif, y);
			side1 = _map->GetPathTile(x, y + 1);
			side2 = _map->GetPathTile(x, y - 1);	
		} 

		if (front != nullptr)
			paths.push_back(front);

		if (side1 != nullptr)
			paths.push_back(side1);

		if (side2 != nullptr)
			paths.push_back(side2);

		if (paths.size() > 1){
			return false;
		} else if (paths.size() == 0){
			throw IncompletePathException();
		} else if (paths.size() == 1){
			if ((*paths.begin())->CanSpawn()){
				return true;
			}

			auto it = std::find(endTiles.begin(), endTiles.end(), *(paths.begin()));
			if (it != endTiles.end())
				return false;


			PathTile* p = *(paths.begin());
			fromX = x;
			fromY = y;
			x = p->GetXPos();
			y = p->GetYPos();
		}
	}

	return false;

}