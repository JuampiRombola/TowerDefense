// using standard exceptions
#include <iostream>
#include <exception>


class ClientDisconnectedException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "El cliente se desconecto";
  }
};
