// using standard exceptions
#include <iostream>
#include <exception>


class SomePlayerJoinedLobbyAndLobbyNotSet : public std::exception
{
  virtual const char* what() const throw()
  {
    return "SomePlayerJoinedLobbyAndLobbyNotSet";
  }
};
