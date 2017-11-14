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


TFServer::TFServer(std::string service) : _playerGUID(1),_connectionHandlers(),_playerProxies(),
_connectionHandlersMutex(), _acceptingConnsMutex(),  _playersProxiesMutex(), _gamesMutex(), _isAcceptingConnections(false),
_lobbyManager(_notifications), _server(service), _notifications(), _gameNotifications(), _games(), _player2game() {
}

TFServer::~TFServer(){
	std::cout << "SHUTDOWN TF SERVER \n" << std::flush;
	Stop();

	_notifications.Release();
	_gameNotifications.Release();

	if (_acceptorThread.joinable())
		_acceptorThread.join();

	if (_notificatorThread.joinable())
		_notificatorThread.join();

	if (_gameNotificatorThread.joinable())
		_notificatorThread.join();

	for (auto it = _connectionHandlers.begin(); it != _connectionHandlers.end(); ++it){
		if ((*it).joinable())
			(*it).join();
	}
	for (auto it = _playerProxies.begin(); it != _playerProxies.end(); ++it)
		delete (*it);
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

void TFServer::_NotifyGamePlayers(){
	GameNotification* gameNoti = _gameNotifications.Dequeue();
	while (gameNoti != nullptr){
		std::cout << "GAME NOTIFICATION FLYING!\n" << std::flush;
		gameNoti->Notify();
		delete gameNoti;
		gameNoti = _gameNotifications.Dequeue();
	}
}




void TFServer::RunServer(){
	_acceptorThread = std::thread(&TFServer::_AcceptConnections, this);
	_notificatorThread = std::thread(&TFServer::_NotifyClients, this);
	_gameNotificatorThread = std::thread(&TFServer::_NotifyGamePlayers, this);
}


void TFServer::HandleConnection(PlayerProxy& player){
	uint8_t opcode;
	try 
	{
		while (true){
			player.sock.Recieve((char*) &opcode, 1);
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

void TFServer::_LaunchGame(Lobby& lobby){
	static int gameId = 1;
	std::lock_guard<std::mutex> lock(_gamesMutex);
	std::vector<PlayerProxy*> playersInGame = lobby.GetPlayingPlayers();
	TowerDefenseGame* game = new TowerDefenseGame(gameId++, _gameNotifications, playersInGame);
	for (auto it = playersInGame.begin(); it != playersInGame.end(); ++it){
		_player2game[(*it)] = game;
	}

	game->Run();
}





void TFServer::_HandleLogin(PlayerProxy& player){
	std::string playerName = player.sock.RecieveString();

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

void TFServer::Stop(){
	std::lock_guard<std::mutex> lock1(_acceptingConnsMutex);
	_isAcceptingConnections = false;

	std::lock_guard<std::mutex> lock2(_connectionHandlersMutex);
	for ( std::thread& handler : _connectionHandlers ) 
    	handler.join();
}