#include <glib.h>
#include "../../include/Exceptions/PlayerLeftTheLobbyAndWasntInIt.h"
#include "../../include/Lobbies/Lobby.h"
#include "../../include/Exceptions/PlayerNotFoundException.h"
#include "../../include/Exceptions/OtherPlayerJoinedLobbyTwice.h"
#include "../../include/GTKNotifications/PlayerLeftJoinedLobbyGTKNotification.h"
#include "../../include/GTKNotifications/PickSpellGTKNotification.h"
#include "../../GTKmm/GTKmmRunner.h"

Lobby::Lobby(std::string& name, uint guid, GTKmmRunner& runner) : _runner(runner), _name(name), _guid(guid), _players(), _otherPlayersMutex(),
_airPlayerGUID(-1), _waterPlayerGUID(-1), _firePlayerGUID(-1), _groundPlayerGUID(-1), pickedMapId(-1)
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

int Lobby::airPlayerGUID(){
	std::lock_guard<std::mutex> lock(_spellsMutex);
	return _airPlayerGUID;
}
int Lobby::waterPlayerGUID(){
	std::lock_guard<std::mutex> lock(_spellsMutex);
	return _waterPlayerGUID;
}
int Lobby::firePlayerGUID(){
	std::lock_guard<std::mutex> lock(_spellsMutex);
	return _firePlayerGUID;
}
int Lobby::groundPlayerGUID(){
	std::lock_guard<std::mutex> lock(_spellsMutex);
	return _groundPlayerGUID;
}

void Lobby::PlayerPickSpell(uint guid, SPELL_TYPE spell_type, bool notify){
	std::lock_guard<std::mutex> lock(_spellsMutex);
	switch(spell_type){
		case SPELL_TYPE_GROUND:
			_groundPlayerGUID =  guid;
			break;
		case SPELL_TYPE_WATER:
			_waterPlayerGUID = guid;
			break;
		case SPELL_TYPE_FIRE:
			_firePlayerGUID = guid;
			break;
		case SPELL_TYPE_AIR:
			_airPlayerGUID = guid;
			break;
	}

	if (!notify)
		return;

	_runner.gtkNotifications.Queue(new PickSpellGTKNotification(guid, spell_type));
	g_idle_add(GTKmmRunner::notification_check, &_runner);
}

uint Lobby::PlayerCount(){
	std::lock_guard<std::mutex> lock(_otherPlayersMutex);
	return _players.size();
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
	_runner.gtkNotifications.Queue(new PlayerLeftJoinedLobbyGTKNotification(player, *this, _runner.lobbyManager->joinedLobby == this, true));
	g_idle_add(GTKmmRunner::notification_check, &_runner);
}

void Lobby::PlayerLeave(OtherPlayer &player){
	std::lock_guard<std::mutex> lock(_otherPlayersMutex);
	auto it = GetOtherPlayer(player.GUID());
	_players.erase(it);
	player.joinedLobby = nullptr;
	if (_waterPlayerGUID == player.GUID())
	_waterPlayerGUID = -1;
	if (_groundPlayerGUID == player.GUID())
		_groundPlayerGUID = -1;
	if (_firePlayerGUID == player.GUID())
		_firePlayerGUID = -1;
	if (_airPlayerGUID == player.GUID())
		_airPlayerGUID = -1;
	_runner.gtkNotifications.Queue(new PlayerLeftJoinedLobbyGTKNotification(player, *this, _runner.lobbyManager->joinedLobby == this, false));
	g_idle_add(GTKmmRunner::notification_check, &_runner);
}

std::vector<OtherPlayer*> Lobby::GetOtherPlayersInLobby(){
	return _players;
}
/*
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
}*/

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