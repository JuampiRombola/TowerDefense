#ifndef __LOBBY_PLAYER__
#define __LOBBY_PLAYER__

#include <string>

class LobbyPlayer{
private:
	std::string _name;
	uint _guid;

public:
	LobbyPlayer(std::string& name, uint guid);
	~LobbyPlayer();
	std::string Name();
	uint GUID();
};


#endif