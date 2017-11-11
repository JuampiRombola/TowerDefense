#include "../../include/GUINotifications/GUINotificationQueue.h"

GUINotificationQueue::GUINotificationQueue() : _notifications(), _mutex() {
	
}

GUINotificationQueue::~GUINotificationQueue(){
	
}

GUINotification* GUINotificationQueue::GetGUINotification(){
	std::lock_guard<std::mutex> lock(_mutex);
	if (_notifications.empty())
		return nullptr;

	GUINotification* noti = _notifications.front();
	_notifications.pop();
	return noti;
}


void GUINotificationQueue::Queue(GUINotification* notification){
  	std::lock_guard<std::mutex> lock(_mutex);
  	_notifications.push(notification);
}
