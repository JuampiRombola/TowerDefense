#ifndef __COMMAND_DISPATCHER__
#define __COMMAND_DISPATCHER__

#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "../../../Common/SocketWrapper.h"
#include "../../../Common/Protocolo.h"
#include "NetCommand.h"

class CommandDispatcher : public std::thread
{
private:
	SocketWrapper& _sock;
    std::queue<NetCommand*> _commands;
	std::mutex _queueLock;
	std::mutex _isEnabledMutex;
    std::condition_variable _cv;
    bool _stop;
	bool _isEnabled;
    std::thread _thread;
    NetCommand* _DequeueCommand();
public:
	CommandDispatcher(SocketWrapper& socket);
	~CommandDispatcher();
    void QueueCommand(NetCommand* command);
	void DispatchCommands();
	void Run();
    void Stop();
	void Disable();
	void Enable();

};
#endif
