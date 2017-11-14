#ifndef __SUBE_SERVER__
#define __SUBE_SERVER__

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <thread>
#include <map>

#include "ServerSocket.h"


#define CARD_SZ 10
#define AMOUNT_SZ 10

#define E_INVAL_AMOUNT 3
#define E_INVAL_CARD 2
#define E_CANT_REGISTER 4

#include <thread>
#include <vector>
#include "PlayerProxy.h"
#include "Lobbies/LobbyManager.h"
#include "ThreadSafeQueue.h"
#include "Notifications/Notification.h"
#include "GameModel/TowerDefenseGame.h"

class TFServer 
{
private:
	uint _playerGUID;
	std::vector<std::thread> _connectionHandlers;
	std::vector<PlayerProxy*> _playerProxies;
	std::mutex _connectionHandlersMutex;
	std::mutex _acceptingConnsMutex;
	std::mutex _playersProxiesMutex;
	std::mutex _gamesMutex;
	bool _isAcceptingConnections;
	LobbyManager _lobbyManager;

	ServerSocket _server;
	ThreadSafeQueue<Notification*> _notifications;
	ThreadSafeQueue<GameNotification*> _gameNotifications;
	std::vector<TowerDefenseGame*> _games;

	std::thread _acceptorThread;
	std::thread _notificatorThread;
	std::thread _gameNotificatorThread;


	std::map<PlayerProxy*, TowerDefenseGame*> _player2game;

	void _AcceptConnections();
	void _NotifyClients();
	void _NotifyGamePlayers();
	void _SetIsAcceptingConnections();
	void _HandleLogin(PlayerProxy& player);
	void _LaunchGame(Lobby& lobby);

public:
//El constructor inicia el socket en modo servidor.
	explicit TFServer(std::string service);
	~TFServer();
	bool ReadyToAcceptConnections();
	bool IsAcceptingConnections();
	void Stop();
	void RunServer();
	void HandleConnection(PlayerProxy& player);
};

#endif
