#ifndef _COMMAND_
#define _COMMAND_

class Command {
public:
	Command();
	virtual ~Command();
	virtual void Execute() = 0;
};

#endif