// using standard exceptions
#include <iostream>
#include <exception>

class UnitCannotMoveDiagonallyException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Units cannot move diagonally";  
	}
};
