#include "../../include/NetCommands/CommandDispatcher.h"

CommandDispatcher::CommandDispatcher(SocketWrapper& socket) : 
_sock(socket), _commands(), _queueLock(), _cv(), _stop(false) {
	
}

CommandDispatcher::~CommandDispatcher(){
	this->Stop();
	if (_thread.joinable())
		_thread.join();
}

void CommandDispatcher::Run(){
	_thread = std::thread(&CommandDispatcher::DispatchCommands, this);
}

void CommandDispatcher::DispatchCommands(){
	NetCommand* cmd = _DequeueCommand();
	while (cmd != nullptr){
		cmd->SendCommand(_sock);
		cmd = _DequeueCommand();
	}
}

void CommandDispatcher::QueueCommand(NetCommand* command){
	if (command == nullptr)
		return;

	std::lock_guard<std::mutex> lock(_queueLock);
    _commands.push(command);
    _cv.notify_one();
}

NetCommand* CommandDispatcher::_DequeueCommand(){
    std::unique_lock<std::mutex> lock(_queueLock);
    while(_commands.empty() && !_stop)
    {
      _cv.wait(lock);
    }

    if (_stop && _commands.empty())
    	return nullptr;

    NetCommand* c = _commands.front();
    _commands.pop();
    return c;
}

void CommandDispatcher::Stop(){
	_stop = true;
	_cv.notify_one();
}