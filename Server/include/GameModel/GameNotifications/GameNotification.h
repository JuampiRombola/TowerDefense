#ifndef __GAME_NOTIFICATION__
#define __GAME_NOTIFICATION__

class GameNotification 
{
public:
	GameNotification();
	virtual ~GameNotification();
	virtual void Notify() = 0;

};

#endif
