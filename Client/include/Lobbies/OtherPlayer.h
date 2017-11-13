#ifndef __LOBBY_PLAYER__
#define __LOBBY_PLAYER__

#include <string>
class Lobby;

class OtherPlayer{
private:
	std::string _name;
	uint _guid;
public:
	OtherPlayer(std::string& name, uint guid);
	~OtherPlayer();
	Lobby* joinedLobby;

	std::string Name();
	uint GUID();

};


#endif