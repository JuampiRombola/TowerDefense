// using standard exceptions
#include <iostream>
#include <exception>

class CannotSpawnWithoutSettingSpawnTilesException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Cannot spawn, there are no spawntiles";  
	}
};
