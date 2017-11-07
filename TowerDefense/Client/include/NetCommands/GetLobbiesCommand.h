#ifndef __GET_LOBBIES_COMAMND__
#define __GET_LOBBIES_COMAMND__

#include <string>
#include "NetCommands/NetCommand.h"

class GetLobbiesCommand : public NetCommand
{
public:
	GetLobbiesCommand();
	~GetLobbiesCommand();
	void SendCommand(SocketWrapper& sock);
};
#endif