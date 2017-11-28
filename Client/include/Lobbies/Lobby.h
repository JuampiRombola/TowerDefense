#ifndef __LOBBY__
#define __LOBBY__

#include <string>
#include <vector>
#include "OtherPlayer.h"
#include "../../../Common/Protocolo.h"
#include <mutex>

class GTKmmRunner;

class Lobby{

private:
	GTKmmRunner& _runner;
	std::string _name;
	uint _guid;
	std::vector<OtherPlayer*> _players;
	std::mutex _otherPlayersMutex;
	std::mutex _spellsMutex;

	int _airPlayerGUID;
	int _waterPlayerGUID;
	int _firePlayerGUID;
	int _groundPlayerGUID;



public:
	Lobby(std::string& name, uint guid, GTKmmRunner& runner);
	~Lobby();

	std::string Name();
	uint GUID();


	uint PlayerCount();

	std::vector<OtherPlayer*>::const_iterator GetOtherPlayer(uint32_t guid);
	void PlayerJoin(OtherPlayer &player);
	void PlayerLeave(OtherPlayer& player);
	std::vector<OtherPlayer*> GetOtherPlayersInLobby();

	void PlayerPickSpell(uint pguid, SPELL_TYPE spell_type, bool notify);

	int airPlayerGUID();
	int waterPlayerGUID();
	int firePlayerGUID();
	int groundPlayerGUID();

	int32_t pickedMapId;

};

#endif