#include "Notifications/LobbyJoinedNotification.h"

#include <iostream>

LobbyJoinedNotification::LobbyJoinedNotification(PlayerProxy& player, Lobby& lobby)
: _player(player), _lobby(lobby) {

}

LobbyJoinedNotification::~LobbyJoinedNotification(){

}

void LobbyJoinedNotification::SetPlayersToNotify(std::vector<PlayerProxy*>* players){
	for (auto it = players->begin(); it != players->end(); ++it){
		PlayerProxy* p = *it;
		if (p->lobby == &_lobby && p != &_player){
			//Solo notifico a los que estan en este lobby
			_playersToNotify.push_back(*it);
		}
	}
}

void LobbyJoinedNotification::Notify(){


	uint8_t opcode = LOBBY_OPCODE;
	_player.sock.Send((char*) &opcode, 1);	
	uint8_t ins = JOIN_LOBBY;
	_player.sock.Send((char*) &ins, 1);
	uint32_t lobbyGUID = _lobby.GUID();
	_player.sock.Send((char*) &lobbyGUID, 4);
	uint8_t amount = _playersToNotify.size();
	_player.sock.Send((char*) &amount, 1);

	std::cout << "SENDING PLAYERS IN LOBBY \n";
	for (auto it = _playersToNotify.begin(); it != _playersToNotify.end(); ++it){

		/// Notifico al jugador que se unio todos los players que tiene en el lobby
		PlayerProxy* p = *it;
		uint32_t pguid = p->GUID();
		_player.sock.Send((char*) &pguid, 4);
		std::string pname = p->Name();
		uint8_t pnamesizebuf = pname.length();
		_player.sock.Send((char*) &pnamesizebuf, 1);
		_player.sock.Send(pname.c_str(), pname.length());

		// Notifico a cada jugador del lobby que un player se unio
		uint8_t opcode2 = LOBBY_OPCODE;
		p->sock.Send((char*) &opcode2, 1);	
		uint8_t ins2 = PLAYER_JOINED_LOBBY;
		p->sock.Send((char*) &ins2, 1);
		uint32_t pGUID = _player.GUID();
		p->sock.Send((char*) &pGUID, 4);
		std::string playername = _player.Name();
		uint8_t pnameSz = playername.length();
		p->sock.Send((char*) &pnameSz, 1);
		p->sock.Send(playername.c_str(), pnameSz);

	}



}