#ifndef __LEAVE_LOBBY_COMMAND_
#define __LEAVE_LOBBY_COMMAND_

#include <string>
#include "../../include/NetCommands/NetCommand.h"

class LeaveLobbyCommand : public NetCommand
{
public:
	LeaveLobbyCommand();
	~LeaveLobbyCommand();
	void SendCommand(SocketWrapper& sock);
};
#endif