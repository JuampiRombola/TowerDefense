#include "../../include/Exceptions/PlayerLeftTheLobbyAndWasntInIt.h"
#include "../../include/Lobbies/Lobby.h"
#include "../../include/Exceptions/PlayerNotFoundException.h"
#include "../../include/Exceptions/OtherPlayerJoinedLobbyTwice.h"


Lobby::Lobby(std::string& name, uint guid) : _name(name), _guid(guid), _players(), _otherPlayersMutex()
{
	std::cout << "Lobby created: id " << guid << ", name " << name << '\n' << std::flush;
}

Lobby::~Lobby(){

}

uint Lobby::GUID(){
	return _guid;
}

std::string Lobby::Name(){
	return _name;
}

void Lobby::PlayerJoin(OtherPlayer &player){
	std::lock_guard<std::mutex> lock(_otherPlayersMutex);
	bool found = true;
	try	{

		std::cout << "INSIDE TRY\n" << std::flush;
		auto it = GetOtherPlayer(player.GUID());
	} catch(const std::exception& e) {
		found = false;
	}

	if (found)
		throw OtherPlayerJoinedLobbyTwice();

	_players.push_back(&player);
}

void Lobby::PlayerLeave(OtherPlayer &player){
	std::lock_guard<std::mutex> lock(_otherPlayersMutex);
	auto it = GetOtherPlayer(player.GUID());
	_players.erase(it);
}

std::vector<OtherPlayer*> Lobby::GetPlayersInLobby(){
	std::vector<OtherPlayer*> otherplayers;
	return _players;
}


std::vector<OtherPlayer*>::const_iterator Lobby::GetOtherPlayer(uint32_t guid){
	bool found = false;
	for (auto it = _players.begin(); it != _players.end() && !found; ++it){
		OtherPlayer* p = *it;
		if (p->GUID() == guid){
			found = true;
			return it;
		}
	}
	throw PlayerNotFoundException();
}