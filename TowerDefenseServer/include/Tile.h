#ifndef __TILE__
#define __TILE__

class Tile{
private:
	uint _xPos;
	uint _yPos;
public:
	Tile(uint xPos, uint yPos);
	virtual ~Tile();
	virtual char GetSymbol() = 0;
	uint GetXPos();
	uint GetYPos();
};

#endif
