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
	uint8_t int8;
	_sock.Recieve((char*) &int8, 1);
	return int8;
}

void PlayerProxy::SendByte(uint8_t int8){
	if (state == DEAD){
		std::cerr << "SENDING BYTE TO DEAD PLAYER\n" << std::flush;
		return;
	}
	_sock.Send((char*) &int8, 1);
}

void PlayerProxy::SendString(std::string &str){
	if (state == DEAD){
		std::cerr << "SENDING STRING TO DEAD PLAYER\n" << std::flush;
		return;
	}
	_sock.SendString(str);
}

std::string PlayerProxy::RecieveString(){
	if (state == DEAD){
		std::cerr << "RECIEVENG STRING FROM DEAD PLAYER\n" << std::flush;
		return "";
	}
	return _sock.RecieveString();
}

int32_t PlayerProxy::RecieveInt32(){
	if (state == DEAD){
		std::cerr << "RECIEVENG INT32 FROM DEAD PLAYER\n" << std::flush;
		return -1;
	}
	uint32_t int32;
	_sock.Recieve((char*) &int32, 4);
	return int32;
}

void PlayerProxy::SendInt32(uint32_t int32){
	if (state == DEAD){
		std::cerr << "SENDING INT32 TO DEAD PLAYER\n" << std::flush;
		return;
	}
	_sock.Send((char*) &int32, 4);
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