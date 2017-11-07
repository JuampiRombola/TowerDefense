#include <Lobbies/Lobby.h>
#include "Exceptions/PlayerLeftTheLobbyAndWasntInIt.h"

Lobby::Lobby(std::string& name, uint guid) : _name(name), _guid(guid), _players()
{

}

Lobby::~Lobby(){
	for (auto it = _players.begin(); it != _players.end(); ++it){
		delete (*it);
	}
}

uint Lobby::GUID(){
	return _guid;
}

std::string Lobby::Name(){
	return _name;
}

void Lobby::AddPlayer(std::string& name, uint guid){
	std::cout << "ADDING PLAYER TO LOBBY WITH GUIID  " << (int) guid << '\n';
	_players.push_back(new LobbyPlayer(name, guid));
}

void Lobby::Reset(){
	_players.clear();
}

void Lobby::PlayerLeft(uint pguid){
	bool found = false;
	LobbyPlayer* p = nullptr;
	auto it = _players.begin();
	for (; it != _players.end() && !found; ++it){
		p = *it;
		uint playerguid = p->GUID();
		std::cout << "CHECKING IF GUID: " << (int) playerguid << " IS THE ONE WHO LEFT\n" << std::flush;
		if (playerguid == pguid){
			std::cout << "FOUND THE PLAYER\n" <<std::flush;
			found = true;
			_players.erase(it);
		}
	}

	if (!found)
		throw PlayerLeftTheLobbyAndWasntInIt();
	
	delete p;

	std::cout << "LLEGO ACA?\n" << std::flush;
}

std::vector<std::string> Lobby::PlayerNames(){
	std::vector<std::string> pnames;
	for (auto it = _players.begin(); it != _players.end(); ++it)
		pnames.push_back((*it)->Name());
	return pnames;
}