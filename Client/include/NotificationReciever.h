#ifndef __NOTIFICATION_RECIEVER__
#define __NOTIFICATION_RECIEVER__

#include <mutex>
#include <thread>
#include <iostream>
#include "../../Common/SocketWrapper.h"
#include "../../Common/Protocolo.h"
#include "Lobbies/ClientLobbyManager.h"

class NotificationReciever : public std::thread
{
	private:
		std::mutex _stopMutex;
		SocketWrapper& _sock;
		ClientLobbyManager& _lobbyManager;
		//GUINotificationQueue& _guiNotifications;
		std::thread _thread;
        GTKRunner& _runner;
		bool _stop;
		bool _Stop();
	public:
		NotificationReciever(SocketWrapper& socket, ClientLobbyManager& lobbyManager, GTKRunner& runner);
		~NotificationReciever();
		void RecieveNotifications();
		void Run();
		void Stop();
};
#endif