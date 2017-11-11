#ifndef THREAD_SAFE_QUEUE
#define THREAD_SAFE_QUEUE

#include <queue>
#include <mutex>
#include <condition_variable>
#include "Notifications/Notification.h"
#include "GameModel/GameNotifications/GameNotification.h"

template <class T>
class ThreadSafeQueue
{
private:
  std::queue<T> _queue;
  mutable std::mutex _mutex;
  std::condition_variable _cv;
  bool _release;
public:
  ThreadSafeQueue() : _queue(), _mutex(), _cv(), _release(false) {

  }

  ~ThreadSafeQueue() {

  }

  void Release(){
  	std::lock_guard<std::mutex> lock(_mutex);
  	_release = true;
  	_cv.notify_one();
  }

  void Queue(T item)
  {
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.push(item);
    _cv.notify_one();
  }

  T Dequeue()
  {
    std::unique_lock<std::mutex> lock(_mutex);
    while(_queue.empty() && !_release)
      _cv.wait(lock);

  	if (_release)
  		return nullptr;

    T item = _queue.front();
    _queue.pop();
    return item;
  }
};

#ifndef __GAME_NOTIFICATION_QUEUE__
#define __GAME_NOTIFICATION_QUEUE__
template class ThreadSafeQueue<GameNotification*>;
#endif

#ifndef __NOTIFICATION_QUEUE__
#define __NOTIFICATION_QUEUE__
template class ThreadSafeQueue<Notification*>;
#endif


#endif