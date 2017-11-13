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
	uint8_t instruction = _pick ? PICK_SPELL : UNPICK_SPELL; ///New lobby
	sock.Send((char*)&instruction, 1);
	uint8_t spell = _spelltype;
    sock.Send((char*)&spell, 1);
}
