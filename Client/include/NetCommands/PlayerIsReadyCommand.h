#ifndef __PLAYER_IS_READY_COMMAND_
#define __PLAYER_IS_READY_COMMAND_

#include <string>

#include "../../include/NetCommands/NetCommand.h"
#include "../../../Common/SocketWrapper.h"

class PlayerIsReadyCommand : public NetCommand{

public:
    PlayerIsReadyCommand();
	~PlayerIsReadyCommand();
	void SendCommand(SocketWrapper& sock);
};

#endif