#ifndef __LOBBY__
#define __LOBBY__

#include <string>
#include <vector>
#include "LobbyPlayer.h"

class Lobby{

private:
	std::string _name;
	uint _guid;
	std::vector<LobbyPlayer*> _players;

public:
	Lobby(std::string& name, uint guid);
	~Lobby();

	std::string Name();
	uint GUID();
	void AddPlayer(std::string& name, uint guid);
	void PlayerLeft(uint pguid);
	void Reset();
	std::vector<std::string> PlayerNames();
};

#endif