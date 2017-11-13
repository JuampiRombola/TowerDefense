#ifndef __LOG_IN_COMMAND__
#define __LOG_IN_COMMAND__

#include <string>

#include "../../include/NetCommands/NetCommand.h"
#include "../../../Common/SocketWrapper.h"

class LogInCommand : public NetCommand{
private:
	std::string _name;
public:
	LogInCommand(std::string& name);
	~LogInCommand();
	void SendCommand(SocketWrapper& sock);
};

#endif