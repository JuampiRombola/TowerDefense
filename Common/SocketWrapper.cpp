#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

#include "SocketWrapper.h"
#include "ClientDisconnectedException.h"
#include "SocketConnectionException.h"

#define USE_CHECK_SUMS 1

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
		rv = send(_fd, &buffer[sentBytes], length - sentBytes, MSG_NOSIGNAL);
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
		rv = recv(_fd, &buffer[bytesRecieved], msgLen - bytesRecieved, MSG_NOSIGNAL);
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
	buffer.resize(lenbuf);
    this->_Recieve(&buffer[0], lenbuf);

    if (USE_CHECK_SUMS){
    	int32_t string_hash = this->RecieveInt32();
    	std::hash<std::string> hash;
   		uint32_t str_actual_hash = hash(buffer) & 0xFFFFFFFF;
 		if (string_hash != str_actual_hash)
 			throw SocketConnectionException();
    }


	return buffer;
}

void SocketWrapper::SendString(std::string& tosend){
	this->SendByte(tosend.length());
    this->_Send(tosend.c_str(), tosend.length());

    if (USE_CHECK_SUMS){
    	std::hash<std::string> hash;
   		uint32_t str_hash = hash(tosend) & 0xFFFFFFFF;
 		this->SendInt32(str_hash);
    }
}

void SocketWrapper::SendByte(uint8_t byte){
    this->_Send((char*) &byte, 1);

	if (USE_CHECK_SUMS) {
		uint8_t check = byte ^ 0xFF;
		this->_Send((char*) &check, 1);
	}
}

uint8_t SocketWrapper::RecieveByte(){
    uint8_t b;
    this->_Recieve((char*) &b, 1);

    if (USE_CHECK_SUMS){
    	uint8_t check;
    	this->_Recieve((char*) &check, 1);
    	uint8_t acutal_check = b ^ 0xFF;
    	if (check != acutal_check)
    		throw SocketConnectionException();
    }

    return b;
}

void SocketWrapper::SendInt32(uint32_t i32){
	uint32_t networkInt32 = htonl(i32);
    this->_Send((char*) &networkInt32, 4);

    if (USE_CHECK_SUMS){
		uint8_t check = 0;
		for (int i = 0; i < 8; i++)
		    check ^= i32 >> (i * 8);
	    this->SendByte(check);
    }
}

uint32_t SocketWrapper::RecieveInt32(){
    uint32_t i;
    this->_Recieve((char*) &i, 4);
    uint32_t i32 = ntohl(i);

    if (USE_CHECK_SUMS){
	    uint32_t check = this->RecieveByte();
	    
	    uint8_t actual_check = 0;
		for (int i = 0; i < 8; i++)
		    actual_check ^= i32 >> (i * 8);

		if (actual_check != check)
			throw SocketConnectionException();
    }


    return i32;
}