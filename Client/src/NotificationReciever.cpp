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
		std::cout << " CHECK \n" << std::flush;
		_sock.Recieve((char*) &opcode, 1);
		std::cout << " RUN \n" << std::flush;
		switch (opcode){
			case CREATE_LOBBY:
				std::cout << "CREATE_LOBBY::\n" << std::flush;
				_lobbyManager.HandleNewLobbyNotification();
				break;
			case JOIN_LOBBY:
				std::cout << "JOIN_LOBBY::\n" << std::flush;
				_lobbyManager.HandleLobbyJoin();
				break;
			case LEAVE_LOBBY:
				std::cout << "LEAVE_LOBBY::\n" << std::flush;
				_lobbyManager.HandleLeaveLobby();
				break;
			case PLAYER_LEFT_LOBBY:
				std::cout << "PLAYER_LEFT_LOBBY::\n" << std::flush;
				_lobbyManager.HandlePlayerLeftLobby();
				break;
			case PLAYER_JOINED_LOBBY:
				std::cout << "PLAYER_JOINED_LOBBY::\n" << std::flush;
				_lobbyManager.HandlePlayerJoinedLobby();
				break;
			case PLAYER_JOIN:
				std::cout << "PLAYER_JOIN::\n" << std::flush;
				_lobbyManager.HandlePlayerJoin();
				break;
			case PLAYER_LEAVE:
				std::cout << "PLAYER_LEAVE::\n" << std::flush;
				_lobbyManager.HandlePlayerLeave();
				break;
			case LOG_IN_SUCCESS:
				std::cout << "LOG_IN_SUCCESS::\n" << std::flush;
				_lobbyManager.HandleLoginSuccess();
				break;
			case LOG_IN_FAILED:
                _runner.gtkNotifications.Queue(new LogInFailedGtkNotification());
				break;
			default:
				std::cout << "UNKNOWN OPCODE RECIEVED: '" << opcode << ", ( " << (int) opcode << ")\'" << std::flush;
		}
		std::cout << " OUT \n" << std::flush;
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