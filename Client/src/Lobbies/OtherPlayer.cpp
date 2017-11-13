#include <iostream>
#include "../../include/Lobbies/OtherPlayer.h"


OtherPlayer::OtherPlayer(std::string& name, uint guid)
: _name(name), _guid(guid), joinedLobby(nullptr)
{
	std::cout << "Other player created: id " << guid << ", name " << name << '\n' << std::flush;

}

OtherPlayer::~OtherPlayer(){

}

std::string OtherPlayer::Name(){
	return _name;
}

uint OtherPlayer::GUID(){
	return _guid;
}