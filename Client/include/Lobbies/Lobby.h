#ifndef __LOBBY__
#define __LOBBY__

#include <string>
#include <vector>
#include "OtherPlayer.h"
#include <mutex>

class Lobby{

private:
	std::string _name;
	uint _guid;
	std::vector<OtherPlayer*> _players;
	std::mutex _otherPlayersMutex;

public:
	Lobby(std::string& name, uint guid);
	~Lobby();

	std::string Name();
	uint GUID();

	std::vector<OtherPlayer*>::const_iterator GetOtherPlayer(uint32_t guid);
	void PlayerJoin(OtherPlayer &player);
	void PlayerLeave(OtherPlayer& player);
	std::vector<OtherPlayer*> GetPlayersInLobby();

};

#endif