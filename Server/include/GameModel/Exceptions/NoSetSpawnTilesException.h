// using standard exceptions
#include <iostream>
#include <exception>

class NoSetSpawnTilesException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "there are no spawntiles";  
	}
};
