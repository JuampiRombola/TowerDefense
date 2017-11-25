#include <iostream>
#include <sstream>
#include <iomanip>
#include "../../include/NetCommands/PickSpellCommand.h"

PickSpellCommand::PickSpellCommand(SPELL_TYPE spelltype, bool pick)
		: _spelltype(spelltype), _pick(pick)
{
	
}

PickSpellCommand::~PickSpellCommand(){
}


void PickSpellCommand::SendCommand(SocketWrapper& sock){
	uint8_t instruction = _pick ? PICK_SPELL : UNPICK_SPELL;
	sock.SendByte(instruction);
	sock.SendByte(_spelltype);
}
