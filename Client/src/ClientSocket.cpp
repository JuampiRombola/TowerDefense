#define _POSIX_C_SOURCE 200112L
extern int errno;
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <string>
#include "../include/ClientSocket.h"
#include "../../Common/SocketWrapper.h"


ClientSocket::ClientSocket(std::string host_name, std::string service)
: SocketWrapper(-1) ,_connected(false) 
{
	_connected = _Connect(host_name, service);
}


ClientSocket::~ClientSocket(){}

bool ClientSocket::Connected(){
	return _connected;
}


bool ClientSocket::_Connect(std::string host_name, std::string service){
	int fd, error;
	struct addrinfo hints, *serv_info, *ptr;
	memset(&hints, 0, sizeof(struct addrinfo));
	error = getaddrinfo(host_name.c_str(), service.c_str(), &hints, &serv_info);
	if (error != 0){
		fprintf(stderr, "connect: getaddrinfo error: %s\n", gai_strerror(error));
		return false;
	}

	bool sock_ok = false, connect_ok = false;
	for(ptr = serv_info;
		ptr != NULL && !sock_ok && !connect_ok;
		ptr = ptr->ai_next){
		if ((fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) <= 0){
			perror("connect: Socket error");
			close(fd);
			freeaddrinfo(serv_info);
			return false;
		} else {
			sock_ok = true;
		}
		if (sock_ok){
			if (connect(fd, ptr->ai_addr, ptr->ai_addrlen) != 0){
				close(fd);
				perror("connect: connect error");
				freeaddrinfo(serv_info);
				return false;
			} else {
				connect_ok = true;
			}
		}
	}

	freeaddrinfo(serv_info);

	if (!connect_ok || !sock_ok){
		return false;
	}

	this->_fd = fd;
	return true;
}
