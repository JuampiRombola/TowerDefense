#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include <utility>
#include <map>
#include <algorithm>
#include <sstream>

#include "../include/TFServer.h"
#include "../../Common/SocketWrapper.h"
#include "../../Common/Protocolo.h"
#include "../include/Notifications/LoggedInNotification.h"
#include "../include/Notifications/InvalidLogInNotification.h"
#include "../include/Notifications/PlayerLeaveNotification.h"
#include "../include/GameModel/Commands/CastSpellCommand.h"


TFServer::TFServer(std::string service) : _playerGUID(1),_connectionHandlers(),_playerProxies(),
 _connectionHandlersMutex(), _acceptingConnsMutex(),  _playersProxiesMutex(), _gamesMutex(), _isAcceptingConnections(false),
 _lobbyManager(_notifications), _server(service), _notifications(), _gameNotificatorThreads(), _player2game(), _game2gameNotifications() {
}

TFServer::~TFServer(){
	_Stop();
	_notifications.Release();

	for (auto it=_game2gameNotifications.begin();
		it!=_game2gameNotifications.end(); ++it){
		it->second->Release();
		delete it->second;
		delete it->first;
	}

	if (_acceptorThread.joinable())
		_acceptorThread.join();

	if (_notificatorThread.joinable())
		_notificatorThread.join();

	for (auto it = _gameNotificatorThreads.begin(); it != _gameNotificatorThreads.end(); ++it){
		if ((*it).joinable()){
			(*it).join();
		}
	}



	for (auto it = _playerProxies.begin(); it != _playerProxies.end(); ++it)
		delete (*it);

	for (auto it = _connectionHandlers.begin(); it != _connectionHandlers.end(); ++it){
		if ((*it).joinable())
			(*it).join();
	}
}

void TFServer::_AcceptConnections(){
	_SetIsAcceptingConnections();
	while (IsAcceptingConnections() && ReadyToAcceptConnections()){
		SocketWrapper* sock = _server.Accept();
		if (sock != nullptr){
			std::lock_guard<std::mutex> lock(_connectionHandlersMutex);
			std::lock_guard<std::mutex> lock1(_playersProxiesMutex);
			_playerProxies.push_back(new PlayerProxy(*sock, ++_playerGUID));
			_connectionHandlers.push_back(std::thread([&] { HandleConnection(*_playerProxies.back()); } ));
		}
	}
}


void TFServer::_NotifyClients(){
	Notification* noti = _notifications.Dequeue();
	while (noti != nullptr){

		{
			std::lock_guard<std::mutex> lock(_playersProxiesMutex);
			noti->SetPlayersToNotify(&_playerProxies);
		}

		noti->Notify();
		delete noti;
		noti = _notifications.Dequeue();
	}
}

void TFServer::_NotifyGamePlayers(ThreadSafeQueue<GameNotification*>* queue, std::vector<PlayerProxy*> players){
	GameNotification* gameNoti = queue->Dequeue();
	while (gameNoti != nullptr){
		gameNoti->Notify(players);
		delete gameNoti;
		gameNoti = queue->Dequeue();
	}
}




void TFServer::RunServer(){
	_acceptorThread = std::thread(&TFServer::_AcceptConnections, this);
	_notificatorThread = std::thread(&TFServer::_NotifyClients, this);
}


void TFServer::_HandleClientLoadedGame(PlayerProxy& player){
	TowerDefenseGame* game = _player2game[&player];
	game->PlayerLoadedGame(player);
}

void TFServer::_HandlePlayerLoadMap(PlayerProxy& player){
	_player2game[&player]->SendMapToPlayer(player);
}



void TFServer::HandleConnection(PlayerProxy& player){
	uint8_t opcode;
	try
	{
		while (true){
			opcode = player.RecieveByte();
			std::cout << "TFSERVER RECIEVED OPCODE " << (int) opcode << '\n';
			switch (opcode){
				case LOG_IN:
					_HandleLogin(player);
					break;
				case CREATE_LOBBY:
					_lobbyManager.HandleCreateNewLobby(player);
					break;
				case JOIN_LOBBY:
					_lobbyManager.HandleJoinLobby(player);
					break;
				case LEAVE_LOBBY:
					_lobbyManager.HandleLeaveLobby(player);
					break;
				case PLAYER_IS_READY:
					_lobbyManager.HandlePlayerIsReady(player);
					if (player.lobby->GameEnabled())
						_LaunchGame(*(player.lobby));
					break;
				case PICK_SPELL:
					_lobbyManager.HandlePlayerPickedSpell(player);
					break;
				case UNPICK_SPELL:
					_lobbyManager.HandlePlayerUnpickedSpell(player);
					break;
				case PICK_MAP:
					_lobbyManager.HandlePickMap(player);
					break;
				case GAME_OPCODE:
					_HandleGameCommand(player);
					break;
				case LOAD_MAP:
					_HandlePlayerLoadMap(player);
					break;
				case CLIENT_LOADED_GAME:
					_HandleClientLoadedGame(player);
					break;
				case IN_GAME_CHAT_MESSAGE:
					_player2game[&player]->ChatMessageFrom(player);
					break;
				default:
					std::cout << "UNKNOWN OPCODE RECIEVED: '" << opcode << "'\n" << std::flush;
			}
		}
	} catch(const std::exception& e) {
		std::cout << "PLAYER GUID: " << (int) player.GUID() << " CONNECTION LOST\n" << std::flush;
		std::lock_guard<std::mutex> lock1(_playersProxiesMutex);
		auto it = std::find(_playerProxies.begin(), _playerProxies.end(), &player);
		if (it != _playerProxies.end()){
			PlayerProxy* playerProxy = *it;
			//_playerProxies.erase(it);
			_notifications.Queue(new PlayerLeaveNotification(playerProxy->GUID()));
			//delete playerProxy;
			playerProxy->state = DEAD;
		}
		std::cerr << e.what() << '\n';
	}
}




void TFServer::_HandleGameCommand(PlayerProxy& player){
	TowerDefenseGame* game = _player2game[&player];
	uint8_t ins = player.RecieveByte();

	if (ins == CLIENT_CAST_SPELL){
		std::cout << "CLIENT CASTED SPELL\n " << std::flush;
		uint8_t spelltype = player.RecieveByte();
		uint32_t x = player.RecieveInt32();
		uint32_t y = player.RecieveInt32();

		game->HandleClientSpellCommand(player, (CAST_SPELL_TYPE) spelltype, x, y );

	}

	if (ins == TOWER_UPGRADE){
		UpgradeType type = (UpgradeType) player.RecieveByte();
		uint x = player.RecieveInt32();
		uint y = player.RecieveInt32();
		game->HandleClientUpgradeTowerCommand(x, y, type);
	}

	if (ins == CLIENT_CREATE_TOWER){
		uint8_t spelltype = player.RecieveByte();
		uint32_t x = player.RecieveInt32();
		uint32_t y = player.RecieveInt32();
		game->HandleClientBuildTowerCommand(player, (SPELL_TYPE) spelltype, x, y);


	}
}




void TFServer::_LaunchGame(Lobby& lobby){
	static int gameId = 1;
	std::lock_guard<std::mutex> lock(_gamesMutex);
	std::vector<PlayerProxy*> playersInGame = lobby.GetPlayingPlayers();

	ThreadSafeQueue<GameNotification*>* notiqueue = new ThreadSafeQueue<GameNotification*>();
	TowerDefenseGame* game = new TowerDefenseGame(gameId++, *notiqueue, playersInGame, *(lobby.MapCfg));
	_game2gameNotifications[game] = notiqueue;
	for (auto it = playersInGame.begin(); it != playersInGame.end(); ++it){
		_player2game[(*it)] = game;
	}

	_gameNotificatorThreads.emplace_back(std::thread(&TFServer::_NotifyGamePlayers, this, notiqueue, playersInGame));
	game->Run(lobby.GetFirePlayer(), lobby.GetAirPlayer(), lobby.GetWaterPlayer(), lobby.GetGroundPlayer());
}





void TFServer::_HandleLogin(PlayerProxy& player){
	std::string playerName = player.RecieveString();

	std::lock_guard<std::mutex> lock1(_playersProxiesMutex);
	for (auto it = _playerProxies.begin(); it != _playerProxies.end(); ++it){
		if ((*it)->Name() == playerName ){
			_notifications.Queue(new InvalidLogInNotification(player));
			return;
		}
	}

	player.SetName(playerName);
	std::cout << " CHECKPOINT \n" << std::flush;
	_lobbyManager.HandleLogin(player);

}

bool TFServer::ReadyToAcceptConnections(){
	return _server.IsListening();
}

void  TFServer::_SetIsAcceptingConnections(){
	std::lock_guard<std::mutex> lock(_acceptingConnsMutex);
	_isAcceptingConnections = true;
}

bool TFServer::IsAcceptingConnections(){
	std::lock_guard<std::mutex> lock(_acceptingConnsMutex);
	return _isAcceptingConnections;
}

void TFServer::_Stop(){
	std::lock_guard<std::mutex> lock1(_acceptingConnsMutex);
	_isAcceptingConnections = false;

	std::lock_guard<std::mutex> lock2(_connectionHandlersMutex);
	for ( std::thread& handler : _connectionHandlers ) 
    	handler.join();
}