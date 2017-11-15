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
	SocketWrapper& _sock;
public:
	PlayerProxy(SocketWrapper& sock, uint guid);
	~PlayerProxy();
	PLAYER_STATE state;
	uint GUID();
	std::string Name();
	void SetName(std::string& name);
	Lobby* lobby;


	void SendByte(uint8_t int8);
	void SendString(std::string &str);
	void SendInt32(uint32_t int32);
	std::string RecieveString();
	int32_t RecieveInt32();
	uint8_t RecieveByte();


};

#endif
