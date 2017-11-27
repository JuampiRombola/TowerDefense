// using standard exceptions
#include <iostream>
#include <exception>


class UnknownOpcodeException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "UnknownOpcodeException";
  }
};
