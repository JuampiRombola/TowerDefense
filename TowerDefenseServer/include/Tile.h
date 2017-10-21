#ifndef __TILE__
#define __TILE__

class Tile{
private:
	unsigned int _xPos;
	unsigned int _yPos;
public:
	Tile(unsigned int xPos, unsigned int yPos);
	virtual ~Tile();
	virtual char GetSymbol() = 0;
	unsigned int GetXPos();
	unsigned int GetYPos();
};

#endif
