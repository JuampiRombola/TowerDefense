
#include "../../include/Lobbies/ClientLobbyManager.h"
#include "../../../Common/Protocolo.h"
#include "../../include/GTKNotifications/NewLobbyGUINotification.h"
#include "../../include/GTKNotifications/JoinedLobbyGUINotification.h"
#include "../../include/GTKNotifications/UpdateLobbyPlayersGUINotification.h"
#include "../../include/Exceptions/JoinedInexistingLobbyException.h"
#include "../../include/Exceptions/SomePlayerLeftLobbyAndLobbyNotSet.h"
#include "../../include/Exceptions/SomePlayerJoinedLobbyAndLobbyNotSet.h"
#include "../../include/GTKNotifications/LeftLobbyGUINotification.h"


ClientLobbyManager::ClientLobbyManager(GUINotificationQueue& guiNotiQueue, SocketWrapper& _sock, GTKRunner& runner)
: _sock(_sock), _lobbies(), _guiNotiQueue(guiNotiQueue), _joinedLobby(nullptr), Runner(runner) {

}

ClientLobbyManager::~ClientLobbyManager(){
	for (auto it = _lobbies.begin(); it != _lobbies.end(); ++it){
		delete (*it);
	}
}


void ClientLobbyManager::HandleNotification(){
	uint8_t opcode;
	_sock.Recieve((char*) &opcode, 1);
	std::cout << "CLIENT LOBBY MANAGER RECIEVED NOTI OPCODE: " << (int) opcode << "\n";
	switch (opcode){
		case CREATE_LOBBY:
			_HandleNewLobbyNotification();
			break;
		case GET_LOBBIES:
			_HandleGetLobbies();
			break;
		case JOIN_LOBBY:
			_HandleLobbyJoin();
			break;
		case PLAYER_LEFT_LOBBY:
			_HandlePlayerLeftLobby();
			break;
		case PLAYER_JOINED_LOBBY:
			_HandlePlayerJoinedLobby();
			break;
		case LEAVE_LOBBY:
			_HandleLeaveLobby();
			break;
		default:
			std::cout << "UNKNOWN LOBBY OPCODE RECIEVED " << (int) opcode <<  "\n";
	}
}

void ClientLobbyManager::_HandleLeaveLobby(){
	_joinedLobby->Reset();
	_joinedLobby = nullptr;
	_guiNotiQueue.Queue(new LeftLobbyGUINotification(_lobbies));
}

void ClientLobbyManager::_HandlePlayerJoinedLobby(){
	uint32_t pguid = -1;
	_sock.Recieve((char*) &pguid, 4);
	uint8_t pnamesz = -1;
	_sock.Recieve((char*) &pnamesz, 1);
	std::string pname = _sock.RecieveString(pnamesz);
	if (_joinedLobby == nullptr)
		throw SomePlayerJoinedLobbyAndLobbyNotSet();

	_joinedLobby->AddPlayer(pname, pguid);	
	std::vector<std::string> pnames = _joinedLobby->PlayerNames();
	_guiNotiQueue.Queue(new UpdateLobbyPlayersGUINotification(pnames));
}

void ClientLobbyManager::_HandlePlayerLeftLobby(){
	uint32_t pguid = -1;
	_sock.Recieve((char*) &pguid, 4);
	if (_joinedLobby == nullptr)
		throw SomePlayerLeftLobbyAndLobbyNotSet();
	std::cout << "HANDLING PLAYER LEFT LOBBY, PGUID: " << (int) pguid << '\n' << std::flush;
	_joinedLobby->PlayerLeft(pguid);
	std::vector<std::string> pnames = _joinedLobby->PlayerNames();
	_guiNotiQueue.Queue(new UpdateLobbyPlayersGUINotification(pnames));
}

void ClientLobbyManager::_HandleLobbyJoin(){
	uint32_t lobbyGuid = -1;
	_sock.Recieve((char*)&lobbyGuid, 4);
	bool found = false;
	Lobby* l = nullptr;

	for (auto it = _lobbies.begin(); it != _lobbies.end() && !found; ++it){
		l = *it;
		if (l->GUID() == lobbyGuid){
			_joinedLobby = l;
			found = true;
		}
	}

	if (!found){
		throw JoinedInexistingLobbyException();
	} 

	uint8_t playersInlobby = -1;
	_sock.Recieve((char*) &playersInlobby, 1);

	for (uint i = 0; i < playersInlobby; i++)
	{
		uint32_t pguid = -1;
		_sock.Recieve((char*)&pguid, 4);
		uint8_t pnamesize;
		_sock.Recieve((char*) &pnamesize, 1);
		std::string pname = _sock.RecieveString(pnamesize);
		l->AddPlayer(pname, pguid);
	}

	std::vector<std::string> pnames = l->PlayerNames();
	_guiNotiQueue.Queue(new JoinedLobbyGUINotification(l->Name(), pnames));

}

void ClientLobbyManager::_HandleNewLobbyNotification(){
	uint32_t lobbyGuid = -1;
	_sock.Recieve((char*)&lobbyGuid, 4);
	uint8_t lobbyNameSize;
	_sock.Recieve((char*) &lobbyNameSize, 1);
	std::string lobbyName = _sock.RecieveString(lobbyNameSize);

	bool found = false;
	for (auto it = _lobbies.begin(); it != _lobbies.end() && !found; ++it){
		Lobby* l = *it;

		if (l->GUID() == lobbyGuid)
			found = true;
	}

	if (!found){
		_lobbies.push_back(new Lobby(lobbyName, lobbyGuid));
 		_guiNotiQueue.Queue(new NewLobbyGUINotification(*(_lobbies.back())));
	}
}

void ClientLobbyManager::_HandleGetLobbies(){

	int32_t lobbyAmount = -1, lobbyGuid = -1;
	_sock.Recieve((char*) &lobbyAmount, 4);
	for (int i = 0; i < lobbyAmount; i++){
		_sock.Recieve((char*)&lobbyGuid, 4);
		uint8_t lobbyNameSize;
		_sock.Recieve((char*) &lobbyNameSize, 1);
		std::string lobbyName = _sock.RecieveString(lobbyNameSize);
		_lobbies.push_back(new Lobby(lobbyName, lobbyGuid));
		_guiNotiQueue.Queue(new NewLobbyGUINotification(*(_lobbies.back())));
	}
}