#ifndef __NOTIFICATION_RECIEVER__
#define __NOTIFICATION_RECIEVER__

#include <thread>
#include <iostream>
#include "../../Common/SocketWrapper.h"
#include "../../Common/Protocolo.h"
#include "Lobbies/ClientLobbyManager.h"
#include "SDLNotifications/GUINotificationQueue.h"

class NotificationReciever : public std::thread
{
	private:
		SocketWrapper& _sock;
		ClientLobbyManager& _lobbyManager;
		GUINotificationQueue& _guiNotifications;
		std::thread _thread;
        GTKRunner& _runner;
	public:
		NotificationReciever(SocketWrapper& socket, ClientLobbyManager& lobbyManager,
                             GUINotificationQueue& guiNotifications, GTKRunner& runner);
		~NotificationReciever();
		void RecieveNotifications();
		void Run();
};
#endif