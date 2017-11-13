// using standard exceptions
#include <iostream>
#include <exception>


class PlayerJoinedInexistingLobbyException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "PlayerJoinedInexistingLobbyException";
  }
};
