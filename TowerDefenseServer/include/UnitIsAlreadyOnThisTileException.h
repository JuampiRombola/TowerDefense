// using standard exceptions
#include <iostream>
#include <exception>

class UnitIsAlreadyOnThisTileException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "Unit is already on this tile";
  }
};
