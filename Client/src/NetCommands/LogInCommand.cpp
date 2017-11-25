#include "../../include/NetCommands/LogInCommand.h"
#include "../../../Common/Protocolo.h"


LogInCommand::LogInCommand(std::string& name) : _name(name) {
	
}

LogInCommand::~LogInCommand(){
	
}


void LogInCommand::SendCommand(SocketWrapper& sock){
	sock.SendByte(LOG_IN);
	sock.SendString(_name);
}