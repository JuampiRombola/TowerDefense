// using standard exceptions
#include <iostream>
#include <exception>

class IncompletePathException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "El camino del mapa no esta completo";
  }
};
