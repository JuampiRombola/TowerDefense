#include "../include/PlayerProxy.h"
#include <iostream>

#include "../include/Lobbies/Lobby.h"


PlayerProxy::PlayerProxy(SocketWrapper& sock, uint guid) 
: _guid(guid), sock(sock), state(LOGIN), lobby(nullptr) {
	
}

PlayerProxy::~PlayerProxy(){
	if (lobby != nullptr){
		lobby->PlayerLeave(*this);
	}
}

uint PlayerProxy::GUID(){
	return _guid;
}

std::string PlayerProxy::Name(){
	return _name;
}

void PlayerProxy::SetName(std::string& name){
	if (state == LOGIN){
		_name = name;
		state = BROWSING_LOBBIES;
	}
}