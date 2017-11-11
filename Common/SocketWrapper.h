#ifndef __SOCKET_WRAPPER__
#define __SOCKET_WRAPPER__

#define CLIENT_DISCONNECTED 0xFF
#define RECEPTION_OK 0xFE
#define ERROR -1

#include <vector>
#include <mutex>
#include <string>

class SocketWrapper 
{
protected:
	int _fd;
public:
	explicit SocketWrapper(int fd);
	~SocketWrapper();
	
	//Envia n bytes del buffer
	//Devuelve falso si el socket se desconecto
	//Lanza una excepcion en caso de error
	bool Send(const char* buffer, size_t n);
	
	//Recibe n bytes del buffer
	//Devuelve falso si el socket se desconecto
	//Lanza una excepcion en caso de error
	bool Recieve(char* buffer, size_t length);

	std::string RecieveString(size_t len);
};

#endif
