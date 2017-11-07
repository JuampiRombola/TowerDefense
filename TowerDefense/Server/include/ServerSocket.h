#ifndef __SERVER_SOCKET_T__
#define __SERVER_SOCKET_T__

#define CLIENT_DISCONNECTED 0xFF
#define RECEPTION_OK 0xFE

#include <vector>
#include <string>
#include "../include/SocketWrapper.h"

class ServerSocket :  public SocketWrapper
{
	private:
		bool _listening;
		std::vector<SocketWrapper*> _clients;
	public:
		//Inicia el servidor en el puerto o servicio pasado por 
		//parametro y abre un socket en modo servidor en el  
		//cual escucha conexiones entrantes.
		explicit ServerSocket(std::string service);
		
		//El desctructor llama close y shutdown
		//sobre todos los file descriptors abiertos.
		~ServerSocket();
		
		//La funcion accept bloquea hasta que obtiene una 
		//conexion valida y devuelve el file descritpor asociado.
		//En caso de error devuelve negativo.
		SocketWrapper* Accept();
		
		//Getter para ver si ya esta escuchando para nuevas conexiones
		bool IsListening();
};
#endif
