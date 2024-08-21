#include <cerrno>
#include <cstddef>
#include <cstring>
#include <fcntl.h>
#include <netdb.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "Server.hpp"
#include "ServerSocket.hpp"
#include <Client.hpp>

ServerSocket::ServerSocket() : Socket(), _registered(false) {}

ServerSocket::~ServerSocket() { freeaddrinfo(_ai); }

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
    if (_fd < 0) {
        freeaddrinfo(ai);
        throw ServerSocket::SocketCreationException();
    }

    this->_ai = ai;
}

void ServerSocket::listen() {
    int yes = 1;

    setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    if (bind(_fd, _ai->ai_addr, _ai->ai_addrlen) < 0)
        throw ServerSocket::BindFailedException();

    if (::listen(_fd, 10) == -1)
        throw ServerSocket::ListenFailedException();

    if (fcntl(_fd, F_SETFL, O_NONBLOCK) < 0)
        throw ServerSocket::ClientNonBlockException();
}

void ServerSocket::onPoll(uint32_t events) {
    (void)events;
    int clientFd = accept(_fd, NULL, NULL);
    if (clientFd < 0) {
        if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
            return;
        throw ServerSocket::AcceptFailedException();
    }

    if (fcntl(clientFd, F_SETFL, O_NONBLOCK) < 0)
        throw ServerSocket::ClientNonBlockException();

    Client* c = new Client(clientFd);
    Server::getInstance().addClient(c);
    std::cout << "Client added\n";
}

bool ServerSocket::isRegistered() { return this->_registered; }

void ServerSocket::setRegistered() { _registered = true; }

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