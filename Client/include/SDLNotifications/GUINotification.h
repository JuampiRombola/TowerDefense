#ifndef __GUI_NOTIFICATION__
#define __GUI_NOTIFICATION__


class GUINotification {
public:
	GUINotification();
	virtual ~GUINotification() = 0;
	virtual void Execute() = 0;
};

#endif