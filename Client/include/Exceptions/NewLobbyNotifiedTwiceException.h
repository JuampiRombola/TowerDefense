// using standard exceptions
#include <iostream>
#include <exception>


class NewLobbyNotifiedTwiceException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "NewLobbyNotifiedTwiceException";
  }
};
