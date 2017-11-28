#include "../../include/NetCommands/CommandDispatcher.h"

CommandDispatcher::CommandDispatcher(SocketWrapper& socket) : 
_sock(socket), _commands(), _queueLock(), _isEnabledMutex(), _cv(), _stop(false), _isEnabled(true) {
	
}

CommandDispatcher::~CommandDispatcher(){
	if (_thread.joinable())
		_thread.join();
}

void CommandDispatcher::Run(){
	_thread = std::thread(&CommandDispatcher::DispatchCommands, this);
}

void CommandDispatcher::DispatchCommands(){
	try{
		NetCommand* cmd = _DequeueCommand();
		while (cmd != nullptr){
			cmd->SendCommand(_sock);
			cmd = _DequeueCommand();
		}
	} catch(const std::exception& e){
		
	}
}

void CommandDispatcher::Disable(){
	std::lock_guard<std::mutex> lock1(_isEnabledMutex);
	std::cout << "Dispatcher disabled\n" << std::flush;
	_isEnabled = false;
}

void CommandDispatcher::Enable(){
	std::lock_guard<std::mutex> lock1(_isEnabledMutex);
	std::cout << "Dispatcher enabled\n" << std::flush;
	_isEnabled = true;
}

void CommandDispatcher::QueueCommand(NetCommand* command){
	if (command == nullptr)
		return;

	std::lock_guard<std::mutex> lock1(_isEnabledMutex);
	if (!_isEnabled){
        std::cout << "dumping command\n" << std::flush;
		delete command;
		return;
	}

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
	std::unique_lock<std::mutex> lock(_queueLock);
	_stop = true;
	_cv.notify_one();
}