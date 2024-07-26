#include "SocketServer.hpp"
#include <cstddef>
#include <cstring>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

SocketServer::SocketServer(const char* port) : Socket() {
    struct addrinfo hints, *ai;
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(NULL, port, &hints, &ai)) != 0)
        throw SocketServer::AddrInfoException();

    this->_fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if (this->_fd < 0) {
        freeaddrinfo(ai);
        throw SocketServer::SocketCreationException();
    }

    this->_ai = ai;
}

SocketServer::~SocketServer() {
    freeaddrinfo(this->_ai);
    close(this->_fd);
}

const char* SocketServer::AddrInfoException::what() const throw() {
    return "Error: Obtention of the local ip failed";
}

const char* SocketServer::SocketCreationException::what() const throw() {
    return "Error: Creation of the local socket failed";
}

const char* SocketServer::BindFailedException::what() const throw() {
    return "Error: Failed to bind the socket";
}

const char* SocketServer::ListenFailedException::what() const throw() {
    return "Error: Failed to listen to the socket";
}

void SocketServer::listen() {
    int yes = 1;

    setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    if (bind(this->_fd, this->_ai->ai_addr, this->_ai->ai_addrlen) < 0)
        throw SocketServer::BindFailedException();

    if (::listen(this->_fd, 10) == -1)
        throw SocketServer::ListenFailedException();
}