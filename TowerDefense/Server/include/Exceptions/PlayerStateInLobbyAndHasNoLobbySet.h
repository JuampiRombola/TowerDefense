// using standard exceptions
#include <iostream>
#include <exception>


class PlayerStateInLobbyAndHasNoLobbySet : public std::exception
{
  virtual const char* what() const throw()
  {
    return "PlayerStateInLobbyAndHasNoLobbySet";
  }
};
