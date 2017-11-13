#include "../../include/Exceptions/PlayerLeftTheLobbyAndWasntInIt.h"
#include "../../include/Lobbies/Lobby.h"
#include "../../include/Exceptions/PlayerNotFoundException.h"
#include "../../include/Exceptions/OtherPlayerJoinedLobbyTwice.h"


Lobby::Lobby(std::string& name, uint guid) : _name(name), _guid(guid), _players(), _otherPlayersMutex(),
_airPlayer(nullptr), _waterPlayer(nullptr), _firePlayer(nullptr), _groundPlayer(nullptr)
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

bool Lobby::FireIsPicked(){
	std::lock_guard<std::mutex> lock(_spellsMutex);
	return _firePlayer != nullptr;
}
bool Lobby::WaterIsPicked(){
	std::lock_guard<std::mutex> lock(_spellsMutex);
	return _waterPlayer != nullptr;
}
bool Lobby::GroundIsPicked(){
	std::lock_guard<std::mutex> lock(_spellsMutex);
	return _groundPlayer != nullptr;
}
bool Lobby::AirIsPicked(){
	std::lock_guard<std::mutex> lock(_spellsMutex);
	return _airPlayer!= nullptr;
}

void Lobby::PlayerPickSpell(OtherPlayer& player, SPELL_TYPE spell_type, bool pick){
	std::lock_guard<std::mutex> lock(_spellsMutex);
	switch(spell_type){
		case SPELL_TYPE_GROUND:
			_groundPlayer = pick ? &player : nullptr;
			break;
		case SPELL_TYPE_WATER:
			_waterPlayer = pick ? &player : nullptr;
			break;
		case SPELL_TYPE_FIRE:
			_firePlayer = pick ? &player : nullptr;
			break;
		case SPELL_TYPE_AIR:
			_airPlayer = pick ? &player : nullptr;
			break;
	}
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

	player.joinedLobby = this;
	_players.push_back(&player);
}

void Lobby::PlayerLeave(OtherPlayer &player){
	std::lock_guard<std::mutex> lock(_otherPlayersMutex);
	auto it = GetOtherPlayer(player.GUID());
	_players.erase(it);
	player.joinedLobby = nullptr;
}

std::vector<OtherPlayer*> Lobby::GetOtherPlayersInLobby(){
	return _players;
}
std::vector<OtherPlayer*> Lobby::GetOtherPlayersInLobbyWithSomeSpellSet(){
	std::lock_guard<std::mutex> lock(_spellsMutex);
	std::vector<OtherPlayer*> otherplayers;
	if (_firePlayer != nullptr)
		otherplayers.push_back(_firePlayer);
	if (_waterPlayer != nullptr)
		otherplayers.push_back(_waterPlayer);
	if (_airPlayer != nullptr)
		otherplayers.push_back(_airPlayer);
	if (_groundPlayer != nullptr)
		otherplayers.push_back(_groundPlayer);
	return otherplayers;
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