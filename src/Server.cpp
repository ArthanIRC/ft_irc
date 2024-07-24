#include "Server.hpp"

Server::Server() {}

Server::Server(int port, std::string password)
    : _port(port), _password(password), _signal(false), _socketFd(-1) {}

Server::~Server() {
    _clientServ.clear();
    _channelServ.clear();
}

void Server::signalHandler(int signal) { this->_signal = true; }

int const& Server::getSocketFd(void) const { return (this->_socketFd); }

void Server::initSocket() {
    _socketAddr.sin_family = AF_INET;
    _socketAddr.sin_port = htons(_port);
    _socketAddr.sin_addr.s_addr = INADDR_ANY;

    _socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (_socketFd == -1)
        throw std::runtime_error("Socket failed");
}