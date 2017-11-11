// using standard exceptions
#include <iostream>
#include <exception>

class SolidGroundAlreadyHasTowerException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "Solid Ground Already Has Tower";
  }
};
