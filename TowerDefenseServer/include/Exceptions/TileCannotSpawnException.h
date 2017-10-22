// using standard exceptions
#include <iostream>
#include <exception>

class TileCannotSpawnException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "No se puede spawnear aca";
  }
};
