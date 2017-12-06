#include <iostream>
#include <algorithm>
#include <iterator>
#include <thread>
#include <chrono>
#include <cmath>
#include <mutex>

#include "../../include/GameModel/Hordes/HordeManager.h"
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
#include "../../include/GameModel/Configuration.h"
#include "../../include/GameModel/Helpers.h"
#include "../../include/GameModel/GameNotifications/UnitCreatedGameNotification.h"
#include "../../include/GameModel/GameNotifications/GameOverGameNotification.h"
#include "../../include/GameModel/GameNotifications/UnitDiedGameNotification.h"
#include "../../include/GameModel/Commands/CastSpellCommand.h"
#include "../../include/GameModel/GameNotifications/GameModelStartedRunningNotification.h"
#include "../../include/GameModel/GameNotifications/MapTransferNotification.h"
#include "../../include/GameModel/GameNotifications/ChatMessageNotification.h"
#include "../../../Common/Paths.h"

TowerDefenseGame::TowerDefenseGame(uint gameId,
	ThreadSafeQueue<GameNotification*>& notifications, std::vector<PlayerProxy*> playersInGame,
    Configuration& mapCfg) :
	_gameStartMutex(), _gameStartCondVariable(), _canGameStart(false),
	_endedMutex(), _commandQueueMutex(), _commands(),_executedCommandQueueMutex(),
	_executedCommands(), _gameStateMutex(),
	 _gameId(gameId),
	_ended(false), _stopped(false), _steps(0), _enemyIdCounter(0), _units(),
	_map(mapCfg.Cfg["ancho"].as<uint>(), mapCfg.Cfg["alto"].as<uint>(), mapCfg), notifications(notifications),
	_players(playersInGame), _ingamePlayers(), _hordeManager(mapCfg)
{
	std::string ss(PATH_CONFIG + std::string("") + "Server/config.yaml");
	GameCfg = new Configuration(ss, 0 ,"Game");
    _hordeManager.game = this;
	_hordeManager.timeToWaitBetweenHordes_ms = GameCfg->Cfg["time_to_wait_between_hordes_ms"].as<uint>();
    clientCooldownManager = new ClientCooldownManager(*GameCfg);
}

TowerDefenseGame::~TowerDefenseGame()
{
	this->Stop();

	for (auto it = _units.begin(); it != _units.end(); ++it)
		delete *it;

	delete GameCfg;
    delete clientCooldownManager;
}


EnviormentUnit* TowerDefenseGame::SpawnAbmonible(){
	uint unitbaseStepDelay_ms = GameCfg->Cfg["unit_base_step_delay_ms"].as<uint>();
	PathTile* spawn = _map.GetRandomSpawnTile();
	uint abmoniblespeed = GameCfg->Cfg["units"]["abmonible"]["speed"].as<uint>();
	uint abmoniblestepdelayms = floor(unitbaseStepDelay_ms / abmoniblespeed);
	uint abmonibleshp = GameCfg->Cfg["units"]["abmonible"]["health_points"].as<uint>();
	EnviormentUnit* unit = new Abmonible(++_enemyIdCounter, abmoniblestepdelayms, abmonibleshp, notifications);
	_units.push_back(unit);
	_map.PlaceUnit(unit, spawn);
	UnitVM vm = unit->GetViewModel();
	notifications.Queue(new UnitCreatedGameNotification(vm));
	return unit;
}
EnviormentUnit* TowerDefenseGame::SpawnHombreCabra(){
	uint unitbaseStepDelay_ms = GameCfg->Cfg["unit_base_step_delay_ms"].as<uint>();
	PathTile* spawn = _map.GetRandomSpawnTile();
	uint hombreCabraSpeed = GameCfg->Cfg["units"]["hombre_cabra"]["speed"].as<uint>();
	uint hombreCabraStepDelay_ms = floor(unitbaseStepDelay_ms / hombreCabraSpeed);
	uint hombreCabraHealthPoints = GameCfg->Cfg["units"]["hombre_cabra"]["health_points"].as<uint>();
	EnviormentUnit* unit = new HombreCabra(++_enemyIdCounter, hombreCabraStepDelay_ms, hombreCabraHealthPoints, notifications);
	_units.push_back(unit);
	_map.PlaceUnit(unit, spawn);
	UnitVM vm = unit->GetViewModel();
	notifications.Queue(new UnitCreatedGameNotification(vm));
	return unit;
}
EnviormentUnit* TowerDefenseGame::SpawnHalconSangriento(){
	uint unitbaseStepDelay_ms = GameCfg->Cfg["unit_base_step_delay_ms"].as<uint>();
	PathTile* spawn = _map.GetRandomSpawnTile();
	uint speed = GameCfg->Cfg["units"]["halcon_sangriento"]["speed"].as<uint>();
	uint stepDelay_ms = floor(unitbaseStepDelay_ms / speed);
	uint hp = GameCfg->Cfg["units"]["halcon_sangriento"]["health_points"].as<uint>();
	EnviormentUnit* unit = new HalconSangriento(++_enemyIdCounter, stepDelay_ms, hp, notifications);
	_units.push_back(unit);
	_map.PlaceUnit(unit, spawn);
	UnitVM vm = unit->GetViewModel();
	notifications.Queue(new UnitCreatedGameNotification(vm));
	return unit;
}
EnviormentUnit* TowerDefenseGame::SpawnDemonioVerde(){
	uint unitbaseStepDelay_ms = GameCfg->Cfg["unit_base_step_delay_ms"].as<uint>();
	PathTile* spawn = _map.GetRandomSpawnTile();
	uint speed = GameCfg->Cfg["units"]["demonio_verde"]["speed"].as<uint>();
	uint stepDelay_ms = floor(unitbaseStepDelay_ms / speed);
	uint hp = GameCfg->Cfg["units"]["demonio_verde"]["health_points"].as<uint>();
	EnviormentUnit* unit = new DemonioVerde(++_enemyIdCounter, stepDelay_ms, hp, notifications);
	_units.push_back(unit);
	_map.PlaceUnit(unit, spawn);
	UnitVM vm = unit->GetViewModel();
	notifications.Queue(new UnitCreatedGameNotification(vm));
	return unit;

}
EnviormentUnit* TowerDefenseGame::SpawnNoMuerto(){
	uint unitbaseStepDelay_ms = GameCfg->Cfg["unit_base_step_delay_ms"].as<uint>();
	PathTile* spawn = _map.GetRandomSpawnTile();
	uint speed = GameCfg->Cfg["units"]["no_muerto"]["speed"].as<uint>();
	uint stepDelay_ms = floor(unitbaseStepDelay_ms / speed);
	uint hp = GameCfg->Cfg["units"]["no_muerto"]["health_points"].as<uint>();
	EnviormentUnit* unit = new NoMuerto(++_enemyIdCounter, stepDelay_ms, hp, notifications);
	_units.push_back(unit);
	_map.PlaceUnit(unit, spawn);
	UnitVM vm = unit->GetViewModel();
	notifications.Queue(new UnitCreatedGameNotification(vm));
	return unit;

}
EnviormentUnit* TowerDefenseGame::SpawnEspectro(){
	uint unitbaseStepDelay_ms = GameCfg->Cfg["unit_base_step_delay_ms"].as<uint>();
	PathTile* spawn = _map.GetRandomSpawnTile();
	uint speed = GameCfg->Cfg["units"]["espectro"]["speed"].as<uint>();
	uint stepDelay_ms = floor(unitbaseStepDelay_ms / speed);
	uint hp = GameCfg->Cfg["units"]["espectro"]["health_points"].as<uint>();
	EnviormentUnit* unit = new Espectro(++_enemyIdCounter, stepDelay_ms, hp, notifications);
	_units.push_back(unit);
	_map.PlaceUnit(unit, spawn);
	UnitVM vm = unit->GetViewModel();
	notifications.Queue(new UnitCreatedGameNotification(vm));
	return unit;
}

void TowerDefenseGame::_SpawnRandomEnemy(){
	uint random_variable = (uint) std::rand() % 6;
	switch (random_variable){
		case 0:
            SpawnAbmonible();
			break;
		case 1:
            SpawnDemonioVerde();
			break;
		case 2:
            SpawnEspectro();
			break;
		case 3:
            SpawnHalconSangriento();
			break;
		case 4:
            SpawnHombreCabra();
			break;
		case 5:
            SpawnNoMuerto();
			break;
	}
}


void TowerDefenseGame::QueueCommand(Command* command){
	std::lock_guard<std::mutex> lock(_commandQueueMutex);
	_commands.push(command);
}

void TowerDefenseGame::PlayersWon() {
	notifications.Queue(new GameOverGameNotification(true));
	_ended = true;
}

void TowerDefenseGame::HandleClientSpellCommand(PlayerProxy& player, CAST_SPELL_TYPE type, uint32_t x, uint32_t y){
	uint cooldown_ms = clientCooldownManager->GetSpellCooldown_ms(type);
    switch(type){
        case SPELL_GRIETA:
            if (&player != _groundPlayer)
                return;
            if (!clientCooldownManager->IsSpellReady(SPELL_GRIETA))
				return;
            break;
        case SPELL_TORNADO:
            if (&player != _airPlayer)
                return;
			if (!clientCooldownManager->IsSpellReady(SPELL_TORNADO))
				return;
            break;
        case SPELL_VENTISCA:
            if (&player != _waterPlayer)
                return;
			if (!clientCooldownManager->IsSpellReady(SPELL_VENTISCA))
				return;
            break;
        case SPELL_CONGELACION:
            if (&player != _waterPlayer)
                return;
			if (!clientCooldownManager->IsSpellReady(SPELL_CONGELACION))
				return;
            break;
        case SPELL_RAYO:
            if (&player != _airPlayer)
                return;
			if (!clientCooldownManager->IsSpellReady(SPELL_RAYO))
				return;
            break;
        case SPELL_METEORITO:
            if (&player != _firePlayer)
                return;
			if (!clientCooldownManager->IsSpellReady(SPELL_METEORITO))
				return;
            break;
        case SPELL_FIREWALL:
            if (&player != _firePlayer)
                return;
			if (!clientCooldownManager->IsSpellReady(SPELL_FIREWALL))
				return;
            break;
        case SPELL_TERRAFORMING:
            if (&player != _groundPlayer)
                return;
			if (!clientCooldownManager->IsSpellReady(SPELL_TERRAFORMING))
				return;
            break;
		case SPELL_PING:
			if (!clientCooldownManager->IsPingForPlayerReady(player))
				return;
			cooldown_ms = clientCooldownManager->GetPingCooldown();
    }
	auto spellcomand = new CastSpellCommand(type, x, y, cooldown_ms, player);
	QueueCommand(spellcomand);
}

void TowerDefenseGame::SendMapToPlayer(PlayerProxy& player){
	notifications.Queue(new MapTransferNotification(_map, player));
}

void TowerDefenseGame::ChatMessageFrom(PlayerProxy& player){
	std::string message = player.RecieveString();
	notifications.Queue(new ChatMessageNotification(message, player));
}



void TowerDefenseGame::PlayerLoadedGame(PlayerProxy& player){
	std::lock_guard<std::mutex> lock(_gameStartMutex);

	auto it = std::find(_ingamePlayers.begin(), _ingamePlayers.end(), &player);

	if (it != _ingamePlayers.end())
		return;

	_ingamePlayers.push_back(&player);

	if (_players.size() == _ingamePlayers.size()){
		_canGameStart = true;
		_gameStartCondVariable.notify_one();
	}
}

void TowerDefenseGame::HandleClientUpgradeTowerCommand(uint x, uint y, UpgradeType type){
	QueueCommand(new UpgradeTowerCommand(x, y, type));
}

void TowerDefenseGame::HandleClientBuildTowerCommand(PlayerProxy& player, SPELL_TYPE spelltype, uint32_t x, uint32_t y ){
	switch(spelltype){
		case SPELL_TYPE_GROUND:
			if (_groundPlayer == &player && clientCooldownManager->IsTowerPlacementReady(spelltype))
				QueueCommand(new BuildTowerCommand(Ground , x, y));
			break;
		case SPELL_TYPE_FIRE:
			if (_firePlayer == &player && clientCooldownManager->IsTowerPlacementReady(spelltype))
				QueueCommand(new BuildTowerCommand(Fire , x, y));
			break;
		case SPELL_TYPE_AIR:
			if (_airPlayer == &player && clientCooldownManager->IsTowerPlacementReady(spelltype))
				QueueCommand(new BuildTowerCommand(Air , x, y));
			break;
		case SPELL_TYPE_WATER:
			if (_waterPlayer == &player && clientCooldownManager->IsTowerPlacementReady(spelltype))
				QueueCommand(new BuildTowerCommand(Water , x, y));
			break;
	}
}


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
	
	for (auto it = _units.begin(); it != _units.end(); ++it){
		(*it)->Step();
	}

	_map.Step(*this);


    for (auto it = _units.begin(); it != _units.end(); ++it){
        if (!((*it)->IsAlive())){
            if (!(*it)->deathNotified){
                UnitVM vm = (*it)->GetViewModel();
                notifications.Queue(new UnitDiedGameNotification(vm));
                _map.RemoveUnit(*it);
                (*it)->deathNotified = true;
            }
        }
    }


	_hordeManager.Step();


	{
		std::lock_guard<std::mutex> lock(_endedMutex);
		std::vector<PathTile*> endTiles = _map.GetFinishTiles();
		for (auto it = endTiles.begin(); it != endTiles.end() && !_ended; ++it){
			_ended |= (*it)->HasAnyUnit();
			if (_ended){
				notifications.Queue(new GameOverGameNotification(false));
			}
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
	std::unique_lock<std::mutex> lock(_gameStartMutex);
	while(!_canGameStart)
		_gameStartCondVariable.wait(lock);
    
	static uint clockFrequency = 10;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    notifications.Queue(new GameModelStartedRunningNotification());


    unsigned long long t1 = Helpers::MillisecondsTimeStamp();
	unsigned long long t2 = 0;
	unsigned long long delta = 0;
	unsigned long long elapsedTime = 0;
	unsigned long long delayTime = 0;

	while(_Step() && !_stopped) {
		t2 = Helpers::MillisecondsTimeStamp();
		elapsedTime = t2 - t1 + delta;
		delayTime = clockFrequency - elapsedTime;
		if (elapsedTime < clockFrequency) {
			std::this_thread::sleep_for(std::chrono::milliseconds(delayTime));
			delta = Helpers::MillisecondsTimeStamp() - t2 - delayTime;
		} else {
			delta = 0;
		}
		t1 = Helpers::MillisecondsTimeStamp();
	}

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
