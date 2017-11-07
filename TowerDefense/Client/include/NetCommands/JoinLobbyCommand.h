#ifndef __JOIN_LOBBY_COMMAND__
#define __JOIN_LOBBY_COMMAND__

#include <string>
#include "NetCommands/NetCommand.h"

class JoinLobbyCommand : public NetCommand
{
private:
	uint _lobbyGUID;
public:
	JoinLobbyCommand(uint lobbyGUID);
	~JoinLobbyCommand();
	void SendCommand(SocketWrapper& sock);
};
#endif