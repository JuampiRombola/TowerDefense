// using standard exceptions
#include <iostream>
#include <exception>

class NonPlacedUnitCannotStepException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "Non placed unit cannot step";
  }
};
