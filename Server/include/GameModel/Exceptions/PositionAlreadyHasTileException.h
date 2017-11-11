// using standard exceptions
#include <iostream>
#include <exception>

class PositionAlreadyHasTileException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "There already is a tile placed there";  
	}
};
