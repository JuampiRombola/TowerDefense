#include "../../include/Notifications/SendLobbiesNotification.h"


SendLobbiesNotification::SendLobbiesNotification(PlayerProxy& player) : _player(player), _toNotify() {

}

SendLobbiesNotification::~SendLobbiesNotification(){

}

void SendLobbiesNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){

}

void SendLobbiesNotification::AddLobby(Lobby* lobby){
	_toNotify.push_back(lobby);
}

void SendLobbiesNotification::Notify(){
		uint8_t opcode = LOBBY_OPCODE;
		_player.sock.Send((char*) &opcode, 1);
		uint8_t instruction = GET_LOBBIES; ///New lobby
		_player.sock.Send((char*) &instruction, 1);

		int32_t lobbyAmount = _toNotify.size();
		_player.sock.Send((char*) &lobbyAmount, 4);

		for (auto it = _toNotify.begin(); it != _toNotify.end(); ++it){
			uint32_t guid = (*it)->GUID();
			std::string name = (*it)->Name();
			_player.sock.Send((char*) &guid, 4);
			uint8_t lobbyNameSizeBuf = name.length();
			_player.sock.Send((char*) &lobbyNameSizeBuf, 1);
			_player.sock.Send(name.c_str(), name.length());

		}

}