// using standard exceptions
#include <iostream>
#include <exception>


class InvalidSpellTypeException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "InvalidSpellTypeException";
  }
};
