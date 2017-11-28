#ifndef __PICK_SPELL_COMMAND_
#define __PICK_SPELL_COMMAND_
#include "../../include/NetCommands/NetCommand.h"
#include "../../../Common/Protocolo.h"

class PickSpellCommand : public NetCommand
{
private:
	SPELL_TYPE _spelltype;
public:
	PickSpellCommand(SPELL_TYPE spelltype);
	~PickSpellCommand();
	void SendCommand(SocketWrapper& sock);
};
#endif