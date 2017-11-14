#define _POSIX_C_SOURCE 200112L
extern int errno;
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/select.h>
#include <string>
#include <vector>
#include "../include/ServerSocket.h"

#define ERROR -1
#define LISTEN_QUEUE_SIZE 10

ServerSocket::ServerSocket(std::string service) : SocketWrapper(-1), _listening(false), _clients()
{
	int fd = -1, error = 0;
	struct addrinfo hints, *server_info, *ptr;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	error = getaddrinfo(NULL, service.c_str(), &hints, &server_info);
	if (error != 0){
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(error));
		return;
	}

	int sock_ok = 0, bind_ok = 0;
	for(ptr = server_info; ptr != NULL && !bind_ok; ptr = ptr->ai_next){
		fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (fd <= 0){
			perror("bind_and_listen: Socket error");
		} else {
			sock_ok = 1;
		}
		if (sock_ok){
			int val = 1;
			if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) != 0){
				perror("bind_and_listen: Set Socket Option Error");
				close(fd);
				freeaddrinfo(server_info);
				return;
			}
			if (bind(fd, ptr->ai_addr, ptr->ai_addrlen) != 0){
				close(fd);
				perror("bind_and_listen: Bind error");
				freeaddrinfo(server_info);
				return;
			} else {
				bind_ok = 1;
			}
		}
	}

	freeaddrinfo(server_info);
	if (sock_ok && bind_ok){
		if (listen(fd, LISTEN_QUEUE_SIZE) != 0){
			perror("bind_and_listen: Listen error");
			close(fd);
		} else {
			_fd = fd;
			_listening = true;
		}
	}
}


SocketWrapper* ServerSocket::Accept(){
	if (!_listening){
		return nullptr;
	}

	int connfd = -1;
	fd_set fdSet;
	struct timeval tv;
	FD_ZERO(&fdSet);
    FD_SET(_fd, &fdSet);
    tv.tv_sec = 2; 
    tv.tv_usec = 0;


    if (select(_fd + 1, &fdSet, NULL, NULL, &tv) > 0) {
		std::cout << "FD " << _fd << '\n';
    	connfd = accept(_fd, (struct sockaddr*) NULL, NULL);
		if (connfd <= 0){
			perror("accept: ");
			return nullptr;
		}
		SocketWrapper* sock = new SocketWrapper(connfd);
		_clients.push_back(sock);
		return sock;
    }

    return nullptr;
}

ServerSocket::~ServerSocket(){
	int a = 0;
	if (a);
	for (auto it = _clients.begin(); it != _clients.end(); ++it){
		SocketWrapper* client = *it;
		delete client;
	}
}

bool ServerSocket::IsListening(){
	return _listening;
}

