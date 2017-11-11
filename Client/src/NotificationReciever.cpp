#include "../include/NotificationReciever.h"
#include "../GTKRunner.h"
#include "../include/GTKNotifications/LogInSuccessGtkNotification.h"
#include "../include/GTKNotifications/LogInFailedGtkNotification.h"


NotificationReciever::NotificationReciever(SocketWrapper& socket, ClientLobbyManager& lobbyManager, GTKRunner& runner)
: _sock(socket), _lobbyManager(lobbyManager),  _runner(runner), _stop(false) {
	
}

NotificationReciever::~NotificationReciever(){
	Stop();
	_thread.join();
}

void NotificationReciever::Run(){
	_thread = std::thread(&NotificationReciever::RecieveNotifications, this);
}

void NotificationReciever::RecieveNotifications(){
	uint8_t opcode;
	while (!_Stop()){
		_sock.Recieve((char*) &opcode, 1);
		std::cout << "CLIENT RECIEVED NOTI OPCODE: " << (int)opcode << "\n";
		switch (opcode){
			case LOBBY_OPCODE:
				_lobbyManager.HandleNotification();
				break;
			case LOG_IN_SUCCESS:
				_runner.gtkNotifications.Queue(new LogInSuccessGtkNotification());
				break;
			case LOG_IN_FAILED:
                _runner.gtkNotifications.Queue(new LogInFailedGtkNotification());
				break;
			default:
				std::cout << "UNKNOWN OPCODE RECIEVED: '" << opcode << '\'' << std::flush;
		}
	}
}

bool NotificationReciever::_Stop(){
	std::lock_guard<std::mutex> lock(_stopMutex);
	return _stop;
}

void NotificationReciever::Stop(){
	std::lock_guard<std::mutex> lock(_stopMutex);
	_stop = true;
}