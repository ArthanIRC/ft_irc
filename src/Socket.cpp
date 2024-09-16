#include <unistd.h>

#include "Socket.hpp"

Socket::Socket() {}

Socket::~Socket() {
    if (_fd >= 0)
        close(_fd);
}

int Socket::getFd() const { return this->_fd; }

const char* Socket::AcceptFailedException::what() const throw() {
    return "Warning: Failed to accept a client socket";
}

const char* Socket::AddrInfoException::what() const throw() {
    return "Error: Obtention of the local ip failed";
}

const char* Socket::BindFailedException::what() const throw() {
    return "Error: Failed to bind the socket";
}

const char* Socket::ClientNonBlockException::what() const throw() {
    return "Warning: Failed to set the client socket to nonblocking";
}

const char* Socket::ConnectException::what() const throw() {
    return "Error: Connection to the server failed.";
}

const char* Socket::ListenFailedException::what() const throw() {
    return "Error: Failed to listen to the socket";
}

const char* Socket::SendException::what() const throw() {
    return "Error: Send failed.";
}

const char* Socket::ServerNonBlockException::what() const throw() {
    return "Error: Failed to set the server socket to nonblocking";
};

const char* Socket::SocketCreationException::what() const throw() {
    return "Error: Creation of the local socket failed";
}
