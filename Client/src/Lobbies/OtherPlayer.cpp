#include "../../include/Lobbies/LobbyPlayer.h"


LobbyPlayer::LobbyPlayer(std::string& name, uint guid)
: _name(name), _guid(guid) {

}

LobbyPlayer::~LobbyPlayer(){

}

std::string LobbyPlayer::Name(){
	return _name;
}

uint LobbyPlayer::GUID(){
	return _guid;
}