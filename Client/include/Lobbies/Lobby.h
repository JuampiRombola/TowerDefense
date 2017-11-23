#ifndef __LOBBY__
#define __LOBBY__

#include <string>
#include <vector>
#include "OtherPlayer.h"
#include "../../../Common/Protocolo.h"
#include <mutex>

class Lobby{

private:
	std::string _name;
	uint _guid;
	std::vector<OtherPlayer*> _players;
	std::mutex _otherPlayersMutex;
	std::mutex _spellsMutex;

	OtherPlayer* _airPlayer;
	OtherPlayer* _waterPlayer;
	OtherPlayer* _firePlayer;
	OtherPlayer* _groundPlayer;



public:
	Lobby(std::string& name, uint guid);
	~Lobby();

	std::string Name();
	uint GUID();



	std::vector<OtherPlayer*>::const_iterator GetOtherPlayer(uint32_t guid);
	void PlayerJoin(OtherPlayer &player);
	void PlayerLeave(OtherPlayer& player);
	std::vector<OtherPlayer*> GetOtherPlayersInLobby();

	void PlayerPickSpell(OtherPlayer& player, SPELL_TYPE spell_type, bool pick);
	std::vector<OtherPlayer*> GetOtherPlayersInLobbyWithSomeSpellSet();
	bool FireIsPicked();
	bool WaterIsPicked();
	bool GroundIsPicked();
	bool AirIsPicked();

	uint32_t pickedMapId;

};

#endif