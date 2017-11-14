#ifndef __NOTIFICATION_RECIEVER__
#define __NOTIFICATION_RECIEVER__

#include <mutex>
#include <thread>
#include <iostream>
#include "../../Common/SocketWrapper.h"
#include "../../Common/Protocolo.h"
#include "Lobbies/ClientLobbyManager.h"
#include "SDLNotifications/SDLNotification.h"
#include "NonBlockingThreadSafeQueue.h"
#include "../View/Model/ModelView.h"

class NotificationReciever : public std::thread
{
private:
	std::mutex _stopMutex;
	SocketWrapper& _sock;
	ClientLobbyManager& _lobbyManager;
	std::thread _thread;
	GTKRunner& _runner;
	bool _stop;
	bool _Stop();
	void _HandleGameOpcode();
	void _HandleTowerPlaced();
    void _HandleUnitPositionUpdate();
    void _HandleUnitCreated();
	void _HandleProjectileFired();
public:
	NotificationReciever(SocketWrapper& socket, ClientLobbyManager& lobbyManager, GTKRunner& runner);
	~NotificationReciever();
	void RecieveNotifications();
	void Run();
	void Stop();
	bool Running();
	ModelView *model_view;

};
#endif