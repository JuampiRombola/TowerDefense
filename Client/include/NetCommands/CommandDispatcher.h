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
    std::condition_variable _cv;
    bool _stop;
    std::thread _thread;
    NetCommand* _DequeueCommand();

	public:
	CommandDispatcher(SocketWrapper& socket);
	~CommandDispatcher();
	void QueueCommand(NetCommand* command);
	void DispatchCommands();
	void Run();
	void Stop();
};
#endif

/*


#ifndef SAFE_QUEUE
#define SAFE_QUEUE

#include <queue>
#include <mutex>
#include <condition_variable>

// A threadsafe-queue.
template <class T>
class SafeQueue
{
public:
  SafeQueue(void)
    : q()
    , m()
    , c()
  {}

  ~SafeQueue(void)
  {}

  // Add an element to the queue.
  void enqueue(T t)
  {
    std::lock_guard<std::mutex> lock(m);
    q.push(t);
    c.notify_one();
  }

  // Get the "front"-element.
  // If the queue is empty, wait till a element is avaiable.
  T dequeue(void)
  {
    std::unique_lock<std::mutex> lock(m);
    while(q.empty())
    {
      // release lock as long as the wait and reaquire it afterwards.
      c.wait(lock);
    }
    T val = q.front();
    q.pop();
    return val;
  }

private:
  std::queue<T> q;
  mutable std::mutex m;
  std::condition_variable c;
};
#endif*/