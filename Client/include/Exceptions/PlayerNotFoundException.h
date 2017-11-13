// using standard exceptions
#include <iostream>
#include <exception>


class InexistingPlayerLeft : public std::exception
{
  virtual const char* what() const throw()
  {
    return "se desconecto un jugador que no teniamos";
  }
};
