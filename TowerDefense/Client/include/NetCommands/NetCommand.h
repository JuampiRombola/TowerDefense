#ifndef __NET_COMMAND__
#define __NET_COMMAND__

#include "SocketWrapper.h"

class NetCommand
{
	public:
		NetCommand();
		virtual ~NetCommand();
		virtual void SendCommand(SocketWrapper& sock) = 0;
};
#endif