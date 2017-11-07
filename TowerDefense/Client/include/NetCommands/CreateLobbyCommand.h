#ifndef __JOIN_LOBBY_COMAMND__
#define __JOIN_LOBBY_COMAMND__

#include <string>
#include "NetCommands/NetCommand.h"
#include "NetCommands/CreateLobbyCommand.h"

class CreateLobbyCommand : public NetCommand
{
private:
	std::string _lobbyName;
public:
	CreateLobbyCommand(std::string lobbyName);
	~CreateLobbyCommand();
	void SendCommand(SocketWrapper& sock);
};
#endif