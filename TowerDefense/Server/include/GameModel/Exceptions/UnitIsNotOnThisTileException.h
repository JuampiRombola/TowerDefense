// using standard exceptions
#include <iostream>
#include <exception>

class UnitIsNotOnThisTileException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "Unit is not on this tile, why would it leave";
  }
};
