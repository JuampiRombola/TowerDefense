// using standard exceptions
#include <iostream>
#include <exception>


class SomePlayerLeftLobbyAndLobbyNotSet : public std::exception
{
  virtual const char* what() const throw()
  {
    return "SomePlayerLeftLobbyAndLobbyNotSet";
  }
};
