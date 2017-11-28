#include <iostream>
#include <sstream>
#include <iomanip>
#include "../../include/NetCommands/PickSpellCommand.h"

PickSpellCommand::PickSpellCommand(SPELL_TYPE spelltype)
		: _spelltype(spelltype)
{
	
}

PickSpellCommand::~PickSpellCommand(){
}


void PickSpellCommand::SendCommand(SocketWrapper& sock){
	sock.SendByte(PICK_SPELL);
	sock.SendByte(_spelltype);
}
