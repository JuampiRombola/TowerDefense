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
private:
	unsigned long long _bytesSent = 0;
	unsigned long long _bytesRecieved = 0;
	//Envia n bytes del buffer
	//Devuelve falso si el socket se desconecto
	//Lanza una excepcion en caso de error
	bool _Send(const char *buffer, size_t n);

	//Recibe n bytes del buffer
	//Devuelve falso si el socket se desconecto
	//Lanza una excepcion en caso de error
	bool _Recieve(char *buffer, size_t length);
protected:
	int _fd;
public:
	explicit SocketWrapper(int fd);
	~SocketWrapper();

	std::string RecieveString();
	void SendString(std::string& tosend);
	void SendByte(uint8_t byte);
	uint8_t RecieveByte();
	void SendInt32(uint32_t byte);
	uint32_t RecieveInt32();

};

#endif
