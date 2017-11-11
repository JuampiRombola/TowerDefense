#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#include "SocketWrapper.h"
#include "ClientDisconnectedException.h"
#include "SocketConnectionException.h"

SocketWrapper::SocketWrapper(int fd) :  _fd(fd) {}

SocketWrapper::~SocketWrapper(){
	if (_fd > 0){
		shutdown(_fd, SHUT_RDWR);
		close(_fd);
	}
}

bool SocketWrapper::Send(const char* buffer, size_t length){
	size_t sentBytes = 0;
	int rv = 0;
	while (sentBytes < length){
		rv = send(_fd, &buffer[sentBytes], length - sentBytes, 0);
		if (rv < 0){
			throw SocketConnectionException();
		} else if (rv == 0){
			throw ClientDisconnectedException();
		} else {
			sentBytes += rv;
		}
	}

	if (sentBytes != length)
		throw SocketConnectionException();
	
	return true;
}
bool SocketWrapper::Recieve(char* buffer, size_t msgLen){
	bool socketIsOpen = true;
	size_t bytesRecieved = 0;
	int rv = 0;
	memset(buffer, 0, msgLen);
	while ((bytesRecieved < msgLen) && socketIsOpen){
		rv = recv(_fd, &buffer[bytesRecieved], msgLen - bytesRecieved, 0);
		if (rv < 0){
			throw SocketConnectionException();
		} else if (rv == 0){
			throw ClientDisconnectedException();
		} else {
			bytesRecieved += rv;
		}
	}

	if (bytesRecieved != msgLen)
		throw SocketConnectionException();
	
	return true;
}


std::string SocketWrapper::RecieveString(size_t len){
	char* buff = new char[len + 1];
	this->Recieve(buff, len);
	buff[len] = '\0';
	std::string str(buff);
	delete buff;
	return str;
}