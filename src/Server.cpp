#include <cstdlib>

#include "Channel.hpp"
#include "Server.hpp"
#include "ServerSocket.hpp"

static const std::string defaultPort = "6667";

Server::Server() {}

Server::~Server() {
    for (std::vector<Client*>::iterator it = _clients.begin();
         it != _clients.end(); it++) {
        _epoll.unsubscribe((*it)->getSocket().getFd());
        delete *it;
    }
    for (std::map<std::string, Channel*>::iterator it = _channels.begin();
         it != _channels.end(); it++) {
        delete it->second;
    }
    if (_socket.isRegistered())
        _epoll.unsubscribe(_socket.getFd());
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

void Server::run() {
    _socket.listen();
    _epoll.subscribe(_socket.getFd(), _socket);
    _socket.setRegistered();

    std::cout << "Listening on " << _port << "\n";
    while (_running) {
        _epoll.poll();
    }
}

void Server::stop() {
    _running = false;
    std::cout << "\nShutting down...\n";
}

void Server::addClient(Client* c) {
    _clients.push_back(c);
    _epoll.subscribe(c->getSocket().getFd(), c->getSocket());
}

Client* Server::findClient(int fd) {
    for (std::vector<Client*>::iterator it = _clients.begin();
         it != _clients.end(); it++) {
        if ((*it)->getSocket().getFd() == fd)
            return *it;
    }
    throw Server::ClientNotFoundException();
}

void Server::removeClient(Client* client) {
    std::vector<Client*>::iterator it =
        std::find(_clients.begin(), _clients.end(), client);
    if (it == _clients.end())
        throw Server::ClientNotFoundException();
    _epoll.unsubscribe(client->getSocket().getFd());
    delete client;
    _clients.erase(it);
}

void Server::removeClient(int fd) { removeClient(findClient(fd)); }

Epoll& Server::getEpoll() { return this->_epoll; }

bool Server::isRunning() const { return this->_running; }

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

const char* Server::ClientNotFoundException::what() const throw() {
    return "Warning: Client was not found in the clients list";
}