// using standard exceptions
#include <iostream>
#include <exception>


class JoinedInexistingLobbyException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "Llego notificacion de que nos unimos a un lobby inexistente";
  }
};
