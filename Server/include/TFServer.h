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

	std::thread _acceptorThread;
	std::thread _notificatorThread;
	std::vector<std::thread> _gameNotificatorThreads;


	std::map<PlayerProxy*, TowerDefenseGame*> _player2game;
	std::map<TowerDefenseGame*, ThreadSafeQueue<GameNotification*>*> _game2gameNotifications;

	void _AcceptConnections();
	void _NotifyClients();
	void _NotifyGamePlayers(ThreadSafeQueue<GameNotification*>* queue, std::vector<PlayerProxy*> players);
	void _SetIsAcceptingConnections();
	void _HandleLogin(PlayerProxy& player);
	void _HandleGameCommand(PlayerProxy& player);
	void _HandlePlayerLoadMap(PlayerProxy& player);
	void _HandleClientLoadedGame(PlayerProxy& player);
	void _LaunchGame(Lobby& lobby);
	void _Stop();

public:
//El constructor inicia el socket en modo servidor.
	explicit TFServer(std::string service);
	~TFServer();
	bool ReadyToAcceptConnections();
	bool IsAcceptingConnections();
	void RunServer();
	void HandleConnection(PlayerProxy& player);
};

#endif
