#include "NetCommands/LogInCommand.h"
#include "../../Protocolo.h"


LogInCommand::LogInCommand(std::string& name) : _name(name) {
	
}

LogInCommand::~LogInCommand(){
	
}


void LogInCommand::SendCommand(SocketWrapper& sock){
	int playerNameSize = _name.length();
	if (playerNameSize > 255)
		return;

	uint8_t opcode = LOG_IN; 
	sock.Send((char*) &opcode, 1);
	char lobbyNameSizeBuf = playerNameSize;
	sock.Send(&lobbyNameSizeBuf, 1);
	sock.Send(_name.c_str(), _name.length());
}