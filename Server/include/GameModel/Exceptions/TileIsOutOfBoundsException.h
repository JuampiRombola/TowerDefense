// using standard exceptions
#include <iostream>
#include <exception>

class TileIsOutOfBoundsException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Tile is out of bounds, cannot place it here";  
	}
};
