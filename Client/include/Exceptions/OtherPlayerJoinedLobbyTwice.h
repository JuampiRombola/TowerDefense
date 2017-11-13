// using standard exceptions
#include <iostream>
#include <exception>


class OtherPlayerJoinedLobbyTwice : public std::exception
{
  virtual const char* what() const throw()
  {
    return "OtherPlayerJoinedLobbyTwice";
  }
};
