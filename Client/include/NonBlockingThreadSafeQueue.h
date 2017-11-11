#ifndef NON_BLOCK_THREAD_SAFE_QUEUE
#define NON_BLOCK_THREAD_SAFE_QUEUE

#include <queue>
#include <mutex>
#include <condition_variable>
#include "GTKNotifications/GTKNotification.h"
#include "SDLNotifications/SDLNotification.h"

template <class T>
class NonBlockingThreadSafeQueue
{
private:
  std::queue<T> _queue;
  mutable std::mutex _mutex;
public:
  NonBlockingThreadSafeQueue() : _queue(), _mutex() {

  }

  ~NonBlockingThreadSafeQueue() {

  }

  void Queue(T item)
  {
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.push(item);
  }

  T Dequeue()
  {
    std::unique_lock<std::mutex> lock(_mutex);
    if (_queue.empty())
        return nullptr;

    T item = _queue.front();
    _queue.pop();
    return item;
  }
};


#ifndef __GTK_NOTIFICATION_QUEUE__
#define __GTK_NOTIFICATION_QUEUE__
template class NonBlockingThreadSafeQueue<GTKNotification*>;
#endif

#ifndef __SDL_NOTIFICATION_QUEUE__
#define __SDL_NOTIFICATION_QUEUE__
template class NonBlockingThreadSafeQueue<SDLNotification*>;
#endif


#endif