// using standard exceptions
#include <iostream>
#include <exception>


class SocketConnectionException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "Error en la comuniacion";
  }
};
