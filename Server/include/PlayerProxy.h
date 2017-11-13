#ifndef __PLAYER_PROXY__
#define __PLAYER_PROXY__

#include <string>

#include "PlayerProxy.h"
#include "../../Common/SocketWrapper.h"
class Lobby;

enum PLAYER_STATE { LOGIN, BROWSING_LOBBIES, IN_LOBBY, IN_GAME, DEAD };

class PlayerProxy 
{
private:
	uint _guid;
	std::string _name;
public:
	PlayerProxy(SocketWrapper& sock, uint guid);
	~PlayerProxy();
	SocketWrapper& sock;
	PLAYER_STATE state;
	uint GUID();
	std::string Name();
	void SetName(std::string& name);
	Lobby* lobby;

};

#endif
