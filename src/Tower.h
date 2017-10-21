#ifndef _TOWER_
#define _TOWER_

class Tower {
protected:
	unsigned long long _lastTimeStamp_ms;
	unsigned int _cooldown_sec;

	virtual void _Fire() = 0; 
	bool _CanFire(); 
public:
	Tower(unsigned int cooldown);
	virtual ~Tower();
	virtual void Step() = 0; 
};

#endif
