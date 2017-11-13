// using standard exceptions
#include <iostream>
#include <exception>


class PlayerDoesNotHaveThisSpellSet : public std::exception
{
  virtual const char* what() const throw()
  {
    return "PlayerDoesNotHaveThisSpellSet";
  }
};
