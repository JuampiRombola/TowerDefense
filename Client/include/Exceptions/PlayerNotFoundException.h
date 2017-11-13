// using standard exceptions
#include <iostream>
#include <exception>


class PlayerNotFoundException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "PlayerNotFoundException";
  }
};
