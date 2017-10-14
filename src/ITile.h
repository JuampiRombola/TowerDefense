#ifndef _ITILE_
#define _ITILE_

class ITile{
public:
	ITile(){};
	virtual ~ITile() {};
	virtual bool AcceptsStructures() = 0;
	virtual bool IsPath() = 0;
	virtual char GetSymbol() = 0;
};

#endif
