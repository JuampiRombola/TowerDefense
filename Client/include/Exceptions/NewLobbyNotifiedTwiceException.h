// using standard exceptions
#include <iostream>
#include <exception>


class PlayerLeftTheLobbyAndWasntInIt : public std::exception
{
  virtual const char* what() const throw()
  {
    return "PlayerLeftTheLobbyAndWasntInIt";
  }
};
