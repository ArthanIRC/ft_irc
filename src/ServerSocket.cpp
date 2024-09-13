#include <arpa/inet.h>
#include <cerrno>
#include <cstddef>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <netdb.h>
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
        throw Socket::AddrInfoException();

    this->_fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if (_fd < 0) {
        freeaddrinfo(ai);
        throw Socket::SocketCreationException();
    }

    this->_ai = ai;
}

void ServerSocket::listen() {
    int yes = 1;

    setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    if (bind(_fd, _ai->ai_addr, _ai->ai_addrlen) < 0)
        throw Socket::BindFailedException();

    if (::listen(_fd, 10) == -1)
        throw Socket::ListenFailedException();

    if (fcntl(_fd, F_SETFL, O_NONBLOCK) < 0)
        throw Socket::ServerNonBlockException();
}

void ServerSocket::onPoll(uint32_t events) {
    (void)events;
    struct sockaddr_in client_addr;
    socklen_t addr_size = sizeof client_addr;

    int clientFd = accept(_fd, (struct sockaddr*)&client_addr, &addr_size);
    if (clientFd < 0) {
        throw Socket::AcceptFailedException();
    }

    if (fcntl(clientFd, F_SETFL, O_NONBLOCK) < 0)
        throw ServerSocket::ClientNonBlockException();

    std::string ip = inet_ntoa(client_addr.sin_addr);

    Client* c = new Client(clientFd, ip);
    Server::getInstance().addClient(c);
    std::cout << "Client added\n";
}

bool ServerSocket::isRegistered() { return this->_registered; }

void ServerSocket::setRegistered() { _registered = true; }