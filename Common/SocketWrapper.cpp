#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

#include "SocketWrapper.h"
#include "ClientDisconnectedException.h"
#include "SocketConnectionException.h"

std::string _FormatBytes(uint bytes){
	if (bytes < 1024)
		return std::to_string(bytes) + " B";
	else if (bytes < (1024 * 1024)) {
		double kBs = (double) bytes / (double) 1024;
		return std::to_string(kBs) + " KB";
	} else
	{
		double MBs = (double) bytes / (double) (1024 * 1024);
		return std::to_string(MBs) + " MB";
	}
}

SocketWrapper::SocketWrapper(int fd) :  _fd(fd) {}

SocketWrapper::~SocketWrapper(){
	std::cout << "Recieved: " << _FormatBytes(_bytesRecieved) << std::endl;
	std::cout << "Sent: " << _FormatBytes(_bytesSent) << std::endl;
	if (_fd > 0){
		shutdown(_fd, SHUT_RDWR);
		close(_fd);
	}
}



bool SocketWrapper::_Send(const char *buffer, size_t length){
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


	_bytesSent += sentBytes;
	return true;
}
bool SocketWrapper::_Recieve(char *buffer, size_t msgLen){
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
	uint8_t lenbuf = RecieveByte();
	std::string buffer;
	buffer.resize(lenbuf + 1);
    this->_Recieve(&buffer[0], lenbuf);
	buffer[lenbuf] = '\0';
	return buffer;
}

void SocketWrapper::SendString(std::string& tosend){
	this->SendByte(tosend.length());
    this->_Send(tosend.c_str(), tosend.length());
}

void SocketWrapper::SendByte(uint8_t byte){
    this->_Send((char*) &byte, 1);
}

uint8_t SocketWrapper::RecieveByte(){
    uint8_t b;
    this->_Recieve((char*) &b, 1);
    return b;
}

void SocketWrapper::SendInt32(uint32_t i32){
	uint32_t networkInt32 = htonl(i32);
    this->_Send((char*) &networkInt32, 4);
}

uint32_t SocketWrapper::RecieveInt32(){
    uint32_t i;
    this->_Recieve((char*) &i, 4);
    return ntohl(i);
}