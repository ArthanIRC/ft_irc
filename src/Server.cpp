#include "Server.hpp"
#include <cstdlib>

Server::Server(int ac, char** data) {
    if (ac < 2 || ac > 3) {
        throw Server::InvalidNumberOfParametersException();
    }
    if (ac == 2) {
        this->_port = this->defaultPort;
        parsePassword(data[1]);
    } else {
        parsePort(data[1]);
        parsePassword(data[2]);
    }
}

Server::~Server() {
    _clientServ.clear();
    _channelServ.clear();
}

const char* Server::InvalidNumberOfParametersException::what() const throw() {
    return "Error: Usage: ./ircserv <port> <password>";
}

const char* Server::InvalidPortException::what() const throw() {
    return "Error: Port has to be between 1 and 65535";
}

const char* Server::EmptyPasswordException::what() const throw() {
    return "Error: Password is empty.";
}

const char* Server::NonAlnumPasswordException::what() const throw() {
    return "Error: Password contains non-alphanumeric characters";
}

int const& Server::getSocketFd(void) const { return (this->_socketFd); }

void Server::parsePort(const char* strp) {
    int port = strtol(strp, NULL, 10);

    if (port < 1 || port > 65535)
        throw Server::InvalidPortException();
    this->_port = port;
}

void Server::parsePassword(std::string pass) {
    if (pass.empty()) {
        throw Server::EmptyPasswordException();
    }
    for (size_t i = 0; i < pass.size(); ++i) {
        if (!isalnum(pass[i])) {
            throw Server::NonAlnumPasswordException();
        }
    }
    this->_password = pass;
}

void Server::initSocket() {
    _socketAddr.sin_family = AF_INET;
    _socketAddr.sin_port = htons(_port);
    _socketAddr.sin_addr.s_addr = INADDR_ANY;

    _socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (_socketFd == -1)
        throw std::runtime_error("Socket failed");
}