#ifndef __GUI_NOTIFICATION__
#define __GUI_NOTIFICATION__


class SDLNotification {
public:
	SDLNotification();
	virtual ~SDLNotification() = 0;
	virtual void Execute() = 0;
};

#endif