#include "ServerSocket.hpp"
#include <Client.hpp>
#include <cstddef>
#include <cstring>
#include <fcntl.h>
#include <netdb.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

ServerSocket::ServerSocket() : Socket() {}

ServerSocket::~ServerSocket() { freeaddrinfo(this->_ai); }

void ServerSocket::init(const char* port) {
    struct addrinfo hints, *ai;
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(NULL, port, &hints, &ai)) != 0)
        throw ServerSocket::AddrInfoException();

    this->_fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if (this->_fd < 0) {
        freeaddrinfo(ai);
        throw ServerSocket::SocketCreationException();
    }

    this->_ai = ai;
}

const char* ServerSocket::AddrInfoException::what() const throw() {
    return "Error: Obtention of the local ip failed";
}

const char* ServerSocket::SocketCreationException::what() const throw() {
    return "Error: Creation of the local socket failed";
}

const char* ServerSocket::BindFailedException::what() const throw() {
    return "Error: Failed to bind the socket";
}

const char* ServerSocket::ListenFailedException::what() const throw() {
    return "Error: Failed to listen to the socket";
}

const char* ServerSocket::AcceptFailedException::what() const throw() {
    return "Error: Failed to accept a client socket";
}

const char* ServerSocket::ClientNonBlockException::what() const throw() {
    return "Error: Failed to set the client socket to nonblocking";
}

void ServerSocket::listen() {
    int yes = 1;

    setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    if (bind(this->_fd, this->_ai->ai_addr, this->_ai->ai_addrlen) < 0)
        throw ServerSocket::BindFailedException();

    if (::listen(this->_fd, 10) == -1)
        throw ServerSocket::ListenFailedException();
}

void ServerSocket::onPoll() {
    int clientFd = accept(this->_fd, NULL, NULL);
    if (clientFd < 0)
        throw ServerSocket::AcceptFailedException();

    if (fcntl(clientFd, F_SETFL, O_NONBLOCK) < 0)
        throw ServerSocket::ClientNonBlockException();

    // TODO: Client creation and assignation to the list of
    // clients for the Server
}