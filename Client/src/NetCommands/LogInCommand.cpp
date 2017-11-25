#include "../../include/NetCommands/LogInCommand.h"
#include "../../../Common/Protocolo.h"


LogInCommand::LogInCommand(std::string& name) : _name(name) {
	
}

LogInCommand::~LogInCommand(){
	
}


void LogInCommand::SendCommand(SocketWrapper& sock){
	uint8_t opcode = LOG_IN;
	sock.SendByte(opcode);
	sock.SendString(_name);
}