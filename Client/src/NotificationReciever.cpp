#include "../include/NotificationReciever.h"
#include "../GTKRunner.h"
#include "../include/GTKNotifications/LogInSuccessGtkNotification.h"
#include "../include/GTKNotifications/LogInFailedGtkNotification.h"


NotificationReciever::NotificationReciever(SocketWrapper& socket, ClientLobbyManager& lobbyManager,
										   GUINotificationQueue& guiNotifications, GTKRunner& runner)
: _sock(socket), _lobbyManager(lobbyManager), _guiNotifications(guiNotifications), _runner(runner) {
	
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
				_runner.GtkNotifications.Queue(new LogInSuccessGtkNotification());
				break;
			case LOG_IN_FAILED:
                _runner.GtkNotifications.Queue(new LogInFailedGtkNotification());
				break;
			default:
				std::cout << "UNKNOWN OPCODE RECIEVED: '" << opcode << '\'' << std::flush;
		}
	}



}

