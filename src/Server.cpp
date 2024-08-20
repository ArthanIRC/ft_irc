#include "Server.hpp"
#include "ServerSocket.hpp"
#include <cstdlib>

static const std::string defaultPort = "6667";

Server::Server() {}

Server::~Server() {
    _clients.clear();
    _channels.clear();
}

void Server::init(int ac, char** data) {
    std::string port;
    std::string password;

    if (ac < 2 || ac > 3) {
        throw Server::InvalidNumberOfParametersException();
    }
    if (ac == 2) {
        port = defaultPort;
        password = parsePassword(data[1]);
    } else {
        port = parsePort(data[1]);
        password = parsePassword(data[2]);
    }

    this->_port = port;
    this->_password = password;
    this->_socket.init(_port.c_str());
    this->_running = true;
}

Server& Server::getInstance() {
    static Server instance;
    return instance;
}

const char* Server::InvalidNumberOfParametersException::what() const throw() {
    return "Error: Usage: ./ircserv <port> <password>";
}

const char* Server::InvalidPortException::what() const throw() {
    return "Error: Port has to be between 1 and 65535";
}

const char* Server::EmptyPasswordException::what() const throw() {
    return "Error: Password is empty";
}

const char* Server::NonAlnumPasswordException::what() const throw() {
    return "Error: Password contains non-alphanumeric characters";
}

std::string Server::parsePort(const char* strp) {
    int port = strtol(strp, NULL, 10);

    if (port < 1 || port > 65535)
        throw Server::InvalidPortException();
    return strp;
}

std::string Server::parsePassword(std::string pass) {
    if (pass.empty()) {
        throw Server::EmptyPasswordException();
    }
    for (size_t i = 0; i < pass.size(); ++i) {
        if (!isalnum(pass[i])) {
            throw Server::NonAlnumPasswordException();
        }
    }
    return pass;
}

void Server::run() { _socket.listen(); }

bool Server::isRunning() const { return this->_running; }