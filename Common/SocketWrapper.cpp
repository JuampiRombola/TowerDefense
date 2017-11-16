#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#include "SocketWrapper.h"
#include "ClientDisconnectedException.h"
#include "SocketConnectionException.h"

SocketWrapper::SocketWrapper(int fd) :  _fd(fd) {}

SocketWrapper::~SocketWrapper(){
	std::cout << "BYTES SENT: " << _bytesSent << "\n" <<std::flush;
	std::cout << "BYTES RECIEVED: " << _bytesRecieved << "\n" <<std::flush;
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


	_bytesSent +- sentBytes;
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

	_bytesRecieved += bytesRecieved;
	return true;
}


std::string SocketWrapper::RecieveString(){
	uint8_t lenbuf = -1;
	this->Recieve((char*) &lenbuf, 1);
	char* buff = new char[lenbuf + 1];
	this->Recieve(buff, lenbuf);
	buff[lenbuf] = '\0';
	std::string str(buff);
	delete buff;
	return str;
}

void SocketWrapper::SendString(std::string& tosend){
	uint8_t bufsz = tosend.length();
	this->Send((char*) &bufsz, 1);
	this->Send(tosend.c_str(), tosend.length());
}