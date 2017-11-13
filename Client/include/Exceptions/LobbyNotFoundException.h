// using standard exceptions
#include <iostream>
#include <exception>

class LobbyNotFoundException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "LobbyNotFoundException";
  }
};
