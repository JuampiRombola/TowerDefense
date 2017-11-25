#include "../include/PlayerProxy.h"
#include <iostream>

#include "../include/Lobbies/Lobby.h"


PlayerProxy::PlayerProxy(SocketWrapper& sock, uint guid) 
: _guid(guid), _sock(sock), state(LOGIN), lobby(nullptr) {
	
}

PlayerProxy::~PlayerProxy(){
	if (lobby != nullptr){
		lobby->PlayerLeave(*this);
	}
}


uint8_t PlayerProxy::RecieveByte(){
	if (state == DEAD)
		return -1;
	return _sock.RecieveByte();
}

void PlayerProxy::SendByte(uint8_t int8){
	if (state == DEAD)
		return;
	_sock.SendByte(int8);
}

void PlayerProxy::SendString(std::string &str){
	if (state == DEAD)
		return;

	_sock.SendString(str);
}

std::string PlayerProxy::RecieveString(){
	if (state == DEAD)
		return "";

	return _sock.RecieveString();
}

int32_t PlayerProxy::RecieveInt32(){
	if (state == DEAD)
		return -1;

	return _sock.RecieveInt32();
}

void PlayerProxy::SendInt32(uint32_t int32){
	if (state == DEAD)
		return;

    _sock.SendInt32(int32);
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