#ifndef __GUI_NOTIF_QUEUE__
#define __GUI_NOTIF_QUEUE__

#include <queue>
#include <mutex>
#include "../../include/GUINotifications/GUINotification.h"

class GUINotificationQueue{
private:
	std::queue<GUINotification*> _notifications;
	std::mutex _mutex;

public:
	GUINotificationQueue();
	~GUINotificationQueue();

	void Queue(GUINotification* notification);
	GUINotification* GetGUINotification();

};


#endif