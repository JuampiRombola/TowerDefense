#include "GUINotifications/NotificationReciever.h"

NotificationReciever::NotificationReciever(SocketWrapper& socket, ClientLobbyManager& lobbyManager, GUINotificationQueue& guiNotifications) 
: _sock(socket), _lobbyManager(lobbyManager), _guiNotifications(guiNotifications) {
	
}

NotificationReciever::~NotificationReciever(){
	_thread.join();
}

void NotificationReciever::Run(){
	_thread = std::thread(&NotificationReciever::RecieveNotifications, this);
}

void NotificationReciever::RecieveNotifications(){
	uint8_t opcode;
	while (true){
		_sock.Recieve((char*) &opcode, 1);
		std::cout << "CLIENT RECIEVED NOTI OPCODE: " << (int)opcode << "\n";
		switch (opcode){
			case LOBBY_OPCODE:
				_lobbyManager.HandleNotification();
				break;
			case LOG_IN_SUCCESS:
				std::cout << "LOGGED IN\n";
				break;
			case LOG_IN_FAILED:
				std::cout << "INVALID LOGIN\n";
				break;
			default:
				std::cout << "UNKNOWN OPCODE RECIEVED: '" << opcode << '\'' << std::flush;
		}
	}



}

