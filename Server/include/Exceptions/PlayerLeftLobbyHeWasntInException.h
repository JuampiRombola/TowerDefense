// using standard exceptions
#include <iostream>
#include <exception>


class PlayerLeftLobbyHeWasntInException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "PlayerLeftLobbyHeWasntInException";
  }
};
