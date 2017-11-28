#include <iostream>
#include <algorithm>

#include "../../include/Lobbies/Lobby.h"
#include "../../include/Exceptions/PlayerLeftLobbyHeWasntInException.h"
#include "../../include/Exceptions/PlayerDoesNotHaveThisSpellSet.h"
#include "../../include/Notifications/PlayerPickedSpellNotification.h"
#include "../../include/Notifications/GameStartedNotification.h"
#include "../../include/Notifications/SpellIsFreeNotification.h"
#include "../../include/Notifications/PlayerLeftLobbyNotification.h"
#include "../../../Common/Protocolo.h"
#include "../../include/Notifications/LobbyJoinedNotification.h"
#include "../../include/Notifications/PlayerIsReadyNotification.h"


Lobby::Lobby(std::string name, uint guid, ThreadSafeQueue<Notification*>& notifications)
 : _playersMutex(), _playerSpellsSlotsMutex(),_readyPlayersMutex(), _gameEnabledMutex(), _guid(guid),
   _name(name), _players(), _notifications(notifications),
   _firePlayer(nullptr),_airPlayer(nullptr), _groundPlayer(nullptr),
   _waterPlayer(nullptr), _readyPlayers(), _gameEnabled(false)
{

}

Lobby::~Lobby(){

}


std::string Lobby::Name(){
	return _name;
}

uint Lobby::GUID(){
	return _guid;
}

void Lobby::PlayerIsReady(PlayerProxy &player) {

	std::lock_guard<std::mutex> lock1(_readyPlayersMutex);
	std::lock_guard<std::mutex> lock3(_playerSpellsSlotsMutex);

	auto it = std::find(_readyPlayers.begin(), _readyPlayers.end(), &player);
	if (it != _readyPlayers.end())
		return;
	_readyPlayers.push_back(&player);
	if (_readyPlayers.size() == _players.size()){
		for (auto it = _players.begin(); it != _players.end(); it++){
			//_playingPlayers.push_back(*it);
			(*it)->state = IN_GAME;
		}


		if (_firePlayer == nullptr){
			std::srand(std::time(0));
			uint random_variable = std::rand() % _players.size();
			_firePlayer = _players[random_variable];
		}
		if (_waterPlayer == nullptr){
			std::srand(std::time(0));
			uint random_variable = std::rand() % _players.size();
			_waterPlayer = _players[random_variable];
		}
		if (_airPlayer == nullptr){
			std::srand(std::time(0));
			uint random_variable = std::rand() % _players.size();
			_airPlayer = _players[random_variable];
		}
		if (_groundPlayer == nullptr){
			std::srand(std::time(0));
			uint random_variable = std::rand() % _players.size();
			_groundPlayer = _players[random_variable];
		}


		std::lock_guard<std::mutex> lock4(_gameEnabledMutex);
		_gameEnabled = true;

		uint superficie = MapCfg->Cfg["superficie"].as<uint>();
		uint width = MapCfg->Cfg["ancho"].as<uint>();
		uint height = MapCfg->Cfg["alto"].as<uint>();
		_notifications.Queue(new GameStartedNotification(*this, superficie, width, height));
	} else {
		_notifications.Queue(new PlayerIsReadyNotification(*this, player));
	}
	/*
	if (_waterPlayer == nullptr || _firePlayer == nullptr || _airPlayer == nullptr || _groundPlayer == nullptr)
		return;

	std::vector<PlayerProxy*> playersAlreadyWithSpell = GetPlayersInLobbyWithSomeSpellSet();
	if (std::find(playersAlreadyWithSpell.begin(), playersAlreadyWithSpell.end(), &player) == playersAlreadyWithSpell.end()){
		//El jugador esta listo pero no eligio spell
		return;
	}
	std::lock_guard<std::mutex> lock1(_readyPlayersMutex);
	std::lock_guard<std::mutex> lock3(_playerSpellsSlotsMutex);

	auto it = std::find(_readyPlayers.begin(), _readyPlayers.end(), &player);
	if (it != _readyPlayers.end())
		return;
	_readyPlayers.push_back(&player);
	if (_readyPlayers.size() == playersAlreadyWithSpell.size()){
		for (auto it = playersAlreadyWithSpell.begin(); it != playersAlreadyWithSpell.end(); it++){
			_playingPlayers.push_back(*it);
			(*it)->state = IN_GAME;
		}

		std::lock_guard<std::mutex> lock4(_gameEnabledMutex);
		_gameEnabled = true;
		
		uint superficie = MapCfg->Cfg["superficie"].as<uint>();
		uint width = MapCfg->Cfg["ancho"].as<uint>();
		uint height = MapCfg->Cfg["alto"].as<uint>();
		_notifications.Queue(new GameStartedNotification(*this, superficie, width, height));
	}*/
}

bool Lobby::GameEnabled(){
	std::lock_guard<std::mutex> lock(_gameEnabledMutex);
	return _gameEnabled;
}

std::vector<PlayerProxy*> Lobby::GetOtherPlayersInLobby(){
	std::lock_guard<std::mutex> lock(_playersMutex);
	return _players;
}

std::vector<PlayerProxy*> Lobby::GetPlayersInLobbyWithSomeSpellSet(){
	std::lock_guard<std::mutex> lock3(_playerSpellsSlotsMutex);
	std::vector<PlayerProxy*> otherplayers;
	
	if (_firePlayer != nullptr)
		otherplayers.push_back(_firePlayer);
	
	if (_waterPlayer != nullptr){
		if (std::find(otherplayers.begin(), otherplayers.end(), _waterPlayer) == otherplayers.end())
			otherplayers.push_back(_waterPlayer);
	}
	if (_airPlayer != nullptr){
		if (std::find(otherplayers.begin(), otherplayers.end(), _airPlayer) == otherplayers.end())
			otherplayers.push_back(_airPlayer);
	}
	if (_groundPlayer != nullptr){
		if (std::find(otherplayers.begin(), otherplayers.end(), _groundPlayer) == otherplayers.end())
			otherplayers.push_back(_groundPlayer);
	}
	return otherplayers;
}


std::vector<PlayerProxy*> Lobby::GetPlayers(){
    std::lock_guard<std::mutex> lock(_playersMutex);
    return _players;
}


std::vector<int> Lobby::GetPlayersGUIDS(){
	std::lock_guard<std::mutex> lock(_playersMutex);
	std::vector<int> playerGUIDS;
	for (auto it = _players.begin(); it != _players.end(); ++it){
		playerGUIDS.emplace_back((*it)->GUID());
	}
	return playerGUIDS;
}

void Lobby::PlayerJoin(PlayerProxy& player){
	// TO DO: fix quien setea player.lobby
	if (GameEnabled())
		return;

	std::lock_guard<std::mutex> lock(_playersMutex);
	if (_players.size() == 4)
		return;
	_players.push_back(&player);
	player.state = IN_LOBBY;
	player.lobby = this;
	_notifications.Queue(new LobbyJoinedNotification(player, *this));

	if (_firePlayer == nullptr){
		_firePlayer = &player;
		_notifications.Queue(new PlayerPickedSpellNotification(player, *this, SPELL_TYPE_FIRE, false));
	} else if (_groundPlayer == nullptr){
		_groundPlayer = &player;
		_notifications.Queue(new PlayerPickedSpellNotification(player, *this, SPELL_TYPE_GROUND, false));
	} else if (_waterPlayer  == nullptr){
		_waterPlayer = &player;
		_notifications.Queue(new PlayerPickedSpellNotification(player, *this, SPELL_TYPE_WATER, false));
	} else if (_airPlayer == nullptr){
		_airPlayer = &player;
		_notifications.Queue(new PlayerPickedSpellNotification(player, *this, SPELL_TYPE_AIR, false));
	}


}

void Lobby::PlayerLeave(PlayerProxy& player){
	if (GameEnabled())
		return;
	std::cout << "PLAYER GUID " << (int) player.GUID() <<  " LEAVING LOBBY\n" << std::flush;
	std::lock_guard<std::mutex> lock(_playersMutex);
	auto it = std::find(_players.begin(), _players.end(), &player);
	PlayerProxy* p = *it;
	if (p == nullptr){
		throw PlayerLeftLobbyHeWasntInException();
	}
	player.state = BROWSING_LOBBIES;
	player.lobby = nullptr;
	_notifications.Queue(new PlayerLeftLobbyNotification(*this, player));
	_players.erase(it);

	std::lock_guard<std::mutex> lock1(_playerSpellsSlotsMutex);

	if (_firePlayer == &player){
		_firePlayer = nullptr;
		_notifications.Queue(new SpellIsFreeNotification( SPELL_TYPE_FIRE, _players));
	}

	if (_waterPlayer == &player){
		_waterPlayer = nullptr;
		_notifications.Queue(new SpellIsFreeNotification( SPELL_TYPE_WATER, _players));
	}

	if (_groundPlayer == &player){
		_groundPlayer = nullptr;
		_notifications.Queue(new SpellIsFreeNotification( SPELL_TYPE_GROUND, _players));
	}

	if (_airPlayer == &player){
		_airPlayer = nullptr;
		_notifications.Queue(new SpellIsFreeNotification( SPELL_TYPE_AIR, _players));
	}

}

void Lobby::PlayerPickFire(PlayerProxy& player){
	if (GameEnabled())
		return;
	std::lock_guard<std::mutex> lock(_playerSpellsSlotsMutex);

	if (_firePlayer != nullptr)
		return;



	if (_waterPlayer == &player){
		_waterPlayer = nullptr;
	} else if (_airPlayer == &player){
		_airPlayer = nullptr;
	} else if (_groundPlayer == &player){
		_groundPlayer = nullptr;
	}


	_firePlayer = &player;
    std::cout << "PLAYER " << player.GUID() << " PICKED FIRE\n" << std::flush;
	_notifications.Queue(new PlayerPickedSpellNotification(player, *this, SPELL_TYPE_FIRE, true));

}

void Lobby::PlayerPickWater(PlayerProxy& player){
	if (GameEnabled())
		return;
	std::lock_guard<std::mutex> lock(_playerSpellsSlotsMutex);

	if (_waterPlayer != nullptr)
		return;

	if (_firePlayer == &player){
		_firePlayer = nullptr;
	} else if (_airPlayer == &player){
		_airPlayer = nullptr;
	} else if (_groundPlayer == &player){
		_groundPlayer = nullptr;
	}

	_waterPlayer = &player;
    std::cout << "PLAYER " << player.GUID() << " PICKED WATER\n" << std::flush;
	_notifications.Queue(new PlayerPickedSpellNotification(player, *this, SPELL_TYPE_WATER, true));
}
void Lobby::PlayerPickAir(PlayerProxy& player){
	if (GameEnabled())
		return;
	std::lock_guard<std::mutex> lock(_playerSpellsSlotsMutex);

	if (_airPlayer != nullptr)
		return;


	if (_waterPlayer == &player){
		_waterPlayer = nullptr;
	} else if (_firePlayer == &player){
		_firePlayer = nullptr;
	} else if (_groundPlayer == &player){
		_groundPlayer = nullptr;
	}



	_airPlayer = &player;
    std::cout << "PLAYER " << player.GUID() << " PICKED AIR\n" << std::flush;
	_notifications.Queue(new PlayerPickedSpellNotification(player, *this, SPELL_TYPE_AIR, true));
}
void Lobby::PlayerPickGround(PlayerProxy& player){
	if (GameEnabled())
		return;
	std::lock_guard<std::mutex> lock(_playerSpellsSlotsMutex);

	if (_groundPlayer != nullptr)
		return;

	if (_waterPlayer == &player){
		_waterPlayer = nullptr; //__notifications.Queue(new PlayerUnpickedSpellNotification(player, *this, SPELL_TYPE_WATER));
	} else if (_firePlayer == &player){
		_firePlayer = nullptr; //__notifications.Queue(new PlayerUnpickedSpellNotification(player, *this, SPELL_TYPE_FIRE));
	} else if (_airPlayer == &player){
		_airPlayer = nullptr; //__notifications.Queue(new PlayerUnpickedSpellNotification(player, *this, SPELL_TYPE_AIR));
	}

	_groundPlayer = &player;
    std::cout << "PLAYER " << player.GUID() << " PICKED GROUND\n" << std::flush;
    _notifications.Queue(new PlayerPickedSpellNotification(player, *this, SPELL_TYPE_GROUND, true));

}

/*
void Lobby::PlayerUnpickFire(PlayerProxy& player){
	if (GameEnabled())
		return;
	std::lock_guard<std::mutex> lock(_playerSpellsSlotsMutex);

	if (_firePlayer != &player)
		throw PlayerDoesNotHaveThisSpellSet();

	_firePlayer = nullptr;
	_notifications.Queue(new PlayerUnpickedSpellNotification(player, *this, SPELL_TYPE_FIRE));
}
void Lobby::PlayerUnpickWater(PlayerProxy& player){
	if (GameEnabled())
		return;
	std::lock_guard<std::mutex> lock(_playerSpellsSlotsMutex);

	if (_waterPlayer != &player)
		throw PlayerDoesNotHaveThisSpellSet();

	_waterPlayer = nullptr;
	_notifications.Queue(new PlayerUnpickedSpellNotification(player, *this, SPELL_TYPE_WATER));
}
void Lobby::PlayerUnpickAir(PlayerProxy& player){
	if (GameEnabled())
		return;
	std::lock_guard<std::mutex> lock(_playerSpellsSlotsMutex);

	if (_airPlayer != &player)
		throw PlayerDoesNotHaveThisSpellSet();

	_airPlayer = nullptr;
	_notifications.Queue(new PlayerUnpickedSpellNotification(player, *this, SPELL_TYPE_AIR));
}
void Lobby::PlayerUnpickGround(PlayerProxy& player){
	if (GameEnabled())
		return;
	std::lock_guard<std::mutex> lock(_playerSpellsSlotsMutex);

	if (_groundPlayer != &player)
		throw PlayerDoesNotHaveThisSpellSet();

	_groundPlayer = nullptr;
	_notifications.Queue(new PlayerUnpickedSpellNotification(player, *this, SPELL_TYPE_GROUND));
}
*/


PlayerProxy* Lobby::GetFirePlayer(){
	std::lock_guard<std::mutex> lock(_playerSpellsSlotsMutex);
	return _firePlayer;
}
PlayerProxy* Lobby::GetWaterPlayer(){
	std::lock_guard<std::mutex> lock(_playerSpellsSlotsMutex);
	return _waterPlayer;
}
PlayerProxy* Lobby::GetAirPlayer(){
	std::lock_guard<std::mutex> lock(_playerSpellsSlotsMutex);
	return _airPlayer;
}
PlayerProxy* Lobby::GetGroundPlayer(){
	std::lock_guard<std::mutex> lock(_playerSpellsSlotsMutex);
	return _groundPlayer;
}
