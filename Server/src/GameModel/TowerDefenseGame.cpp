#include <iostream>
#include <algorithm>
#include <iterator>
#include <thread>
#include <chrono>
#include <cmath>
#include <mutex>

#include "../../include/GameModel/TowerDefenseGame.h"
#include "../../include/GameModel/Map/Map.h"
#include "../../include/GameModel/EnviormentUnits/DemonioVerde.h"
#include "../../include/GameModel/EnviormentUnits/Abmonible.h"
#include "../../include/GameModel/EnviormentUnits/Espectro.h"
#include "../../include/GameModel/EnviormentUnits/NoMuerto.h"
#include "../../include/GameModel/EnviormentUnits/HalconSangriento.h"
#include "../../include/GameModel/EnviormentUnits/HombreCabra.h"
#include "../../include/GameModel/EnviormentUnits/EnviormentUnit.h"
#include "../../include/GameModel/Towers/Tower.h"
#include "../../include/GameModel/Towers/GroundTower.h"
#include "../../include/GameModel/GameConfiguration.h"
#include "../../include/GameModel/Helpers.h"
#include "../../include/GameModel/GameNotifications/UnitCreatedGameNotification.h"
#include "../../include/GameModel/GameNotifications/GameOverGameNotification.h"
#include "../../include/GameModel/GameNotifications/UnitDiedGameNotification.h"
#include "../../include/GameModel/Commands/CastSpellCommand.h"

TowerDefenseGame::TowerDefenseGame(uint gameId,
	ThreadSafeQueue<GameNotification*>& notifications, std::vector<PlayerProxy*> playersInGame) :
	_endedMutex(), _commandQueueMutex(), _commands(),_executedCommandQueueMutex(), 
	_executedCommands(), _gameStateMutex(),
	 _gameId(gameId),
	_ended(false), _stopped(false), _steps(0), _enemyIdCounter(0), _units(),
	_map(9, 9, "map.yaml"), notifications(notifications), _players(playersInGame)
{
	std::string ss("config.yaml");
	GameCfg = new GameConfiguration(ss);
    _clientCooldownManager = new ClientCooldownManager(*GameCfg);
//	mv->createTower(1, TORRE_TIERRA, 2, 0);
//	mv->createTower(2, TORRE_AIRE, 2, 2);
//	mv->createTower(3, TORRE_FUEGO, 1, 4);
//	mv->createTower(4, TORRE_AGUA, 4, 6);

	//this->QueueCommand(new BuildTowerCommand(Ground, 2, 0));
	//this->QueueCommand(new BuildTowerCommand(Air, 2, 2));
	//this->QueueCommand(new BuildTowerCommand(Fire, 1, 4));
	//this->QueueCommand(new BuildTowerCommand(Water, 4, 6));
}

TowerDefenseGame::~TowerDefenseGame()
{
	this->Stop();

	for (auto it = _units.begin(); it != _units.end(); ++it)
		delete *it;

	delete GameCfg;
    delete _clientCooldownManager;
}


void TowerDefenseGame::_SpawnAbmonible(){
	uint unitbaseStepDelay_ms = GameCfg->Cfg["unit_base_step_delay_ms"].as<uint>();
	PathTile* spawn = _map.GetRandomSpawnTile();
	uint abmoniblespeed = GameCfg->Cfg["units"]["abmonible"]["speed"].as<uint>();
	uint abmoniblestepdelayms = floor(unitbaseStepDelay_ms / abmoniblespeed);
	uint abmonibleshp = GameCfg->Cfg["units"]["abmonible"]["health_points"].as<uint>();
	EnviormentUnit* unit = new Abmonible(++_enemyIdCounter, abmoniblestepdelayms, abmonibleshp, notifications);
	_units.push_back(unit);
	_map.PlaceUnit(unit, spawn);
	UnitVM vm = unit->GetViewModel();
	notifications.Queue(new UnitCreatedGameNotification(vm, _players));
}
void TowerDefenseGame::_SpawnHombreCabra(){
	uint unitbaseStepDelay_ms = GameCfg->Cfg["unit_base_step_delay_ms"].as<uint>();
	PathTile* spawn = _map.GetRandomSpawnTile();
	uint hombreCabraSpeed = GameCfg->Cfg["units"]["hombre_cabra"]["speed"].as<uint>();
	uint hombreCabraStepDelay_ms = floor(unitbaseStepDelay_ms / hombreCabraSpeed);
	uint hombreCabraHealthPoints = GameCfg->Cfg["units"]["hombre_cabra"]["health_points"].as<uint>();
	EnviormentUnit* unit = new HombreCabra(++_enemyIdCounter, hombreCabraStepDelay_ms, hombreCabraHealthPoints, notifications);
	_units.push_back(unit);
	_map.PlaceUnit(unit, spawn);
	UnitVM vm = unit->GetViewModel();
	notifications.Queue(new UnitCreatedGameNotification(vm, _players));
}
void TowerDefenseGame::_SpawnHalconSangriento(){
	uint unitbaseStepDelay_ms = GameCfg->Cfg["unit_base_step_delay_ms"].as<uint>();
	PathTile* spawn = _map.GetRandomSpawnTile();
	uint speed = GameCfg->Cfg["units"]["halcon_sangriento"]["speed"].as<uint>();
	uint stepDelay_ms = floor(unitbaseStepDelay_ms / speed);
	uint hp = GameCfg->Cfg["units"]["halcon_sangriento"]["health_points"].as<uint>();
	EnviormentUnit* unit = new HalconSangriento(++_enemyIdCounter, stepDelay_ms, hp, notifications);
	_units.push_back(unit);
	_map.PlaceUnit(unit, spawn);
	UnitVM vm = unit->GetViewModel();
	notifications.Queue(new UnitCreatedGameNotification(vm, _players));
}
void TowerDefenseGame::_SpawnDemonioVerde(){
	uint unitbaseStepDelay_ms = GameCfg->Cfg["unit_base_step_delay_ms"].as<uint>();
	PathTile* spawn = _map.GetRandomSpawnTile();
	uint speed = GameCfg->Cfg["units"]["demonio_verde"]["speed"].as<uint>();
	uint stepDelay_ms = floor(unitbaseStepDelay_ms / speed);
	uint hp = GameCfg->Cfg["units"]["demonio_verde"]["health_points"].as<uint>();
	EnviormentUnit* unit = new DemonioVerde(++_enemyIdCounter, stepDelay_ms, hp, notifications);
	_units.push_back(unit);
	_map.PlaceUnit(unit, spawn);
	UnitVM vm = unit->GetViewModel();
	notifications.Queue(new UnitCreatedGameNotification(vm, _players));
}
void TowerDefenseGame::_SpawnNoMuerto(){
	uint unitbaseStepDelay_ms = GameCfg->Cfg["unit_base_step_delay_ms"].as<uint>();
	PathTile* spawn = _map.GetRandomSpawnTile();
	uint speed = GameCfg->Cfg["units"]["no_muerto"]["speed"].as<uint>();
	uint stepDelay_ms = floor(unitbaseStepDelay_ms / speed);
	uint hp = GameCfg->Cfg["units"]["no_muerto"]["health_points"].as<uint>();
	EnviormentUnit* unit = new NoMuerto(++_enemyIdCounter, stepDelay_ms, hp, notifications);
	_units.push_back(unit);
	_map.PlaceUnit(unit, spawn);
	UnitVM vm = unit->GetViewModel();
	notifications.Queue(new UnitCreatedGameNotification(vm, _players));
}
void TowerDefenseGame::_SpawnEspectro(){
	uint unitbaseStepDelay_ms = GameCfg->Cfg["unit_base_step_delay_ms"].as<uint>();
	PathTile* spawn = _map.GetRandomSpawnTile();
	uint speed = GameCfg->Cfg["units"]["espectro"]["speed"].as<uint>();
	uint stepDelay_ms = floor(unitbaseStepDelay_ms / speed);
	uint hp = GameCfg->Cfg["units"]["espectro"]["health_points"].as<uint>();
	EnviormentUnit* unit = new Espectro(++_enemyIdCounter, stepDelay_ms, hp, notifications);
	_units.push_back(unit);
	_map.PlaceUnit(unit, spawn);
	UnitVM vm = unit->GetViewModel();
	notifications.Queue(new UnitCreatedGameNotification(vm, _players));
}

void TowerDefenseGame::_SpawnRandomEnemy(){
	uint random_variable = (uint) std::rand() % 6;
	switch (random_variable){
		case 0:
			_SpawnAbmonible();
			break;
		case 1:
			_SpawnDemonioVerde();
			break;
		case 2:
			_SpawnEspectro();
			break;
		case 3:
			_SpawnHalconSangriento();
			break;
		case 4:
			_SpawnHombreCabra();
			break;
		case 5:
			_SpawnNoMuerto();
			break;
	}
}


void TowerDefenseGame::QueueCommand(Command* command){
	std::lock_guard<std::mutex> lock(_commandQueueMutex);
	_commands.push(command);
}

void TowerDefenseGame::HandleClientSpellCommand(PlayerProxy& player, CAST_SPELL_TYPE type, uint32_t x, uint32_t y){
	//
    switch(type){
        case SPELL_GRIETA:
            if (&player != _groundPlayer)
                return;
            if (!_clientCooldownManager->IsSpellReady(SPELL_GRIETA))
				return;
            break;
        case SPELL_TORNADO:
            if (&player != _airPlayer)
                return;
			if (!_clientCooldownManager->IsSpellReady(SPELL_TORNADO))
				return;
            break;
        case SPELL_VENTISCA:
            if (&player != _waterPlayer)
                return;
			if (!_clientCooldownManager->IsSpellReady(SPELL_VENTISCA))
				return;
            break;
        case SPELL_CONGELACION:
            if (&player != _waterPlayer)
                return;
			if (!_clientCooldownManager->IsSpellReady(SPELL_CONGELACION))
				return;
            break;
        case SPELL_RAYO:
            if (&player != _airPlayer)
                return;
			if (!_clientCooldownManager->IsSpellReady(SPELL_RAYO))
				return;
            break;
        case SPELL_METEORITO:
            if (&player != _firePlayer)
                return;
			if (!_clientCooldownManager->IsSpellReady(SPELL_METEORITO))
				return;
            break;
        case SPELL_FIREWALL:
            if (&player != _firePlayer)
                return;
			if (!_clientCooldownManager->IsSpellReady(SPELL_FIREWALL))
				return;
            break;
        case SPELL_TERRAFORMING:
            if (&player != _groundPlayer)
                return;
			if (!_clientCooldownManager->IsSpellReady(SPELL_TERRAFORMING))
				return;
            break;

    }

	QueueCommand(new CastSpellCommand(type, x, y));
}

void TowerDefenseGame::HandleClientBuildTowerCommand(PlayerProxy& player, SPELL_TYPE spelltype, uint32_t x, uint32_t y ){



	switch(spelltype){
		case SPELL_TYPE_GROUND:
			if (_groundPlayer == &player && _clientCooldownManager->IsTowerPlacementReady(spelltype))
				QueueCommand(new BuildTowerCommand(Ground , x, y));
			break;
		case SPELL_TYPE_FIRE:
			if (_firePlayer == &player && _clientCooldownManager->IsTowerPlacementReady(spelltype))
				QueueCommand(new BuildTowerCommand(Fire , x, y));
			break;
		case SPELL_TYPE_AIR:
			if (_airPlayer == &player && _clientCooldownManager->IsTowerPlacementReady(spelltype))
				QueueCommand(new BuildTowerCommand(Air , x, y));
			break;
		case SPELL_TYPE_WATER:
			if (_waterPlayer == &player && _clientCooldownManager->IsTowerPlacementReady(spelltype))
				QueueCommand(new BuildTowerCommand(Water , x, y));
			break;
	}
}

/*
Command* TowerDefenseGame::GetExecutedCommand(){
	std::lock_guard<std::mutex> lock(_executedCommandQueueMutex);
	if (_executedCommands.size() == 0)
		return nullptr;
	
	Command* c = _executedCommands.front();
	_executedCommands.pop();
	return c;
}*/

EnviormentUnit* TowerDefenseGame::GetUnit(uint id){
	for(auto it = _units.begin(); it != _units.end(); ++it){
		if ((*it)->GetId() == id)
			return *it;
	}
	return nullptr;
}

void TowerDefenseGame::_ExecuteCommands(){
	std::lock_guard<std::mutex> lock(_commandQueueMutex);
	while (!_commands.empty()){
		Command* c =_commands.front();
		_commands.pop();
		c->Execute(&_map, this, notifications);
		delete c;
	}
}



bool TowerDefenseGame::_Step(){
	static unsigned long long ts = 0;
	unsigned long long actualTs = Helpers::MillisecondsTimeStamp();

	std::lock_guard<std::mutex> gamelock(_gameStateMutex);
	_ExecuteCommands();

	_steps = _steps + 1;

	uint32_t spawnrandomenemyevery_ms = 4000;
	if (actualTs - ts > spawnrandomenemyevery_ms){
		ts = actualTs;
		_SpawnRandomEnemy();
	}

	for (auto it = _units.begin(); it != _units.end(); ++it){
		(*it)->Step(*this);
	}

	_map.Step(*this);

	auto it = _units.begin();
	if (it != _units.end()){
		for (; it != _units.end();){
			if (!((*it)->IsAlive())){
				std::cout << "REMOVING DEAD UNIT\n";
				UnitVM vm = (*it)->GetViewModel();
				notifications.Queue(new UnitDiedGameNotification(vm, _players));
				_map.RemoveUnit(*it);
				EnviormentUnit* unit = *it;
				_units.erase(it);
				delete unit;
			} else {
				++it;
			}
		}
	}

	{
		std::lock_guard<std::mutex> lock(_endedMutex);
		std::vector<PathTile*> endTiles = _map.GetFinishTiles();
		for (auto it = endTiles.begin(); it != endTiles.end() && !_ended; ++it){
			_ended = (*it)->HasAnyUnit();
		}
	}

	return !_ended;
}


bool TowerDefenseGame::Ended(){
	std::lock_guard<std::mutex> lock(_endedMutex);
	return _ended;
}

void TowerDefenseGame::Run(PlayerProxy* fireplayer, PlayerProxy* airplayer, PlayerProxy* waterplayer, PlayerProxy* groundplayer){
	_airPlayer = airplayer;
    _waterPlayer = waterplayer;
    _groundPlayer = groundplayer;
    _firePlayer = fireplayer;

    _thread = std::thread(&TowerDefenseGame::_Run, this);
}

void TowerDefenseGame::Stop(){
	_stopped = true;
	if (_thread.joinable())
		_thread.join();
}

void TowerDefenseGame::_Run()
{
	static uint clockFrequency = 100;
    std::this_thread::sleep_for (std::chrono::milliseconds(10000));
    unsigned long long lastTimestamp = Helpers::MillisecondsTimeStamp();
	unsigned long long timestamp = 0;
	unsigned long long delta = 0;
	unsigned long long diference = 0;
	while(_Step() && !_stopped) {
		timestamp = Helpers::MillisecondsTimeStamp();
		delta = timestamp - lastTimestamp;
		diference = clockFrequency - delta;

		if (diference >= 0)
			std::this_thread::sleep_for (std::chrono::milliseconds(diference));
		else
			std::cout << "\n\nClock delayed " << diference * -1 << " ms\n\n" << std::flush;
	}

	notifications.Queue(new GameOverGameNotification(_players));
	//
	// Por ahora solo se puede perder.
	// jeje que juego divertido.
	//

	std::cout << "GAME OVER! \n";
}

	std::vector<UnitVM> TowerDefenseGame::GetUnitViewModels(){
	std::lock_guard<std::mutex> lock(_gameStateMutex);
	std::vector<UnitVM> uVms;
	for (auto it = _units.begin(); it != _units.end(); ++it){
		uVms.push_back((*it)->GetViewModel());
	}
	return uVms;
}


std::vector<ProjectileVM> TowerDefenseGame::GetProjectileViewModels(){
	std::lock_guard<std::mutex> lock(_gameStateMutex);
	std::vector<Projectile*> projs = _map.GetProjectiles();
	std::vector<ProjectileVM> pVms;
	for (auto it = projs.begin(); it != projs.end(); ++it){
		pVms.push_back((*it)->GetViewModel());
	}
	return pVms;
}

std::vector<TowerVM> TowerDefenseGame::GetTowerViewModels(){
	std::lock_guard<std::mutex> lock(_gameStateMutex);
	std::vector<TowerVM> t;
	std::vector<Tower*> towers = _map.GetTowers();
	for (auto it = towers.begin(); it != towers.end(); ++it){
		t.push_back((*it)->GetViewModel());
	}
	return t;
}

std::vector<PlayerProxy*> TowerDefenseGame::GetPlayers(){
	return _players;
}


uint TowerDefenseGame::GetID(){
	return _gameId;
}
