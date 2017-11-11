#ifndef __CLIENT_SOCKET_T__
#define __CLIENT_SOCKET_T__

#include <string>
#include "SocketWrapper.h"

class ClientSocket final : public SocketWrapper
{
	private:
		bool _connected;
		bool _Connect(std::string host_name, std::string service);
	public:
		//Constructor a partir de un hostname y servicio
		//Se conecta automaticamente en el constructor
		ClientSocket(std::string host_name, std::string service);

		//Destructor default
		~ClientSocket();
		
		//Getter para saber si esta conectado.
		bool Connected();
};
#endif
