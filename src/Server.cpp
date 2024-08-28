#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <set>

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "ServerSocket.hpp"

using std::map;
using std::set;
using std::string;
using std::vector;

static const string defaultPort = "6667";
static const string motd =
    "In effect, we conjure the spirits of the computer with our spells.";
static const string networkName = "ArThAn";
static const string serverName = "JUSTICE";
static const string userModes = "ior";
static const string version = "1.0.0";
static const string creationDate = "27/07/2024";

Server::Server() {}

Server::~Server() {
    for (vector<Client*>::iterator it = _clients.begin(); it != _clients.end();
         it++) {
        try {
            _epoll.unsubscribe((*it)->getSocket().getFd());
        } catch (Epoll::EpollUnsubscribeException& e) {
            std::cerr << e.what() << "\n";
        }
        delete *it;
    }
    for (map<string, Channel*>::iterator it = _channels.begin();
         it != _channels.end(); it++) {
        delete it->second;
    }
    if (_socket.isRegistered())
        try {
            _epoll.unsubscribe(_socket.getFd());
        } catch (Epoll::EpollUnsubscribeException& e) {
            std::cerr << e.what() << "\n";
        }
}

void Server::init(int ac, char** data) {
    string port;
    string password;

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

    _operators["thibrac"] = "pirate";
    _operators["andrew"] = "saske";
    _operators["arluc"] = "crepuscule";
    this->_port = port;
    this->_password = password;
    this->_socket.init(_port.c_str());
    this->_running = true;
}

Server& Server::getInstance() {
    static Server instance;
    return instance;
}

string Server::parsePort(const char* strp) {
    int port = strtol(strp, NULL, 10);

    if (port < 1 || port > 65535)
        throw Server::InvalidPortException();
    return strp;
}

string Server::parsePassword(std::string pass) {
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

void Server::addChannel(Channel* c) {
    string name = c->getName();
    if (_channels.find(name) != _channels.end()) {
        throw;
    }
    _channels[name] = c;
}

Client* Server::findClient(int fd) {
    for (vector<Client*>::iterator it = _clients.begin(); it != _clients.end();
         it++) {
        if ((*it)->getSocket().getFd() == fd)
            return *it;
    }
    throw Server::ClientNotFoundException();
}

Client* Server::findClient(string nickname) {
    for (vector<Client*>::iterator it = _clients.begin(); it != _clients.end();
         it++) {
        if ((*it)->isRegistered() && (*it)->getNickname() == nickname)
            return *it;
    }
    throw Server::ClientNotFoundException();
}

Channel* Server::findChannel(string name) {
    std::map<string, Channel*>::iterator it = _channels.find(name);
    if (it == _channels.end()) {
        throw Server::ChannelNotFoundException();
    }
    return it->second;
}

void Server::removeClient(Client* client) {
    vector<Client*>::iterator it =
        std::find(_clients.begin(), _clients.end(), client);
    if (it == _clients.end())
        throw Server::ClientNotFoundException();
    _epoll.unsubscribe(client->getSocket().getFd());
    delete client;
    _clients.erase(it);
}

void Server::removeClient(int fd) { removeClient(findClient(fd)); }

std::string Server::getPrefix() { return this->_prefix; }

vector<Client*> Server::getClients() { return this->_clients; }

map<std::string, Channel*> Server::getChannels() { return this->_channels; }

map<std::string, std::string> Server::getOperators() {
    return this->_operators;
}

Epoll& Server::getEpoll() { return this->_epoll; }

string Server::getPassword() const { return this->_password; }

string Server::getMotd() const { return motd; }

string Server::getNetworkName() const { return networkName; }

string Server::getServerName() const { return serverName; }

string Server::getVersion() const { return version; }

string Server::getCreationDate() const { return creationDate; }

bool Server::isRunning() const { return this->_running; }

void Server::sendMessage(Channel* channel, string message) {
    map<string, Client*> clients = channel->getClients();
    for (map<string, Client*>::iterator it = clients.begin();
         it != clients.end(); it++)
        it->second->sendMessage(message);
}

void Server::sendMessage(map<string, Channel*> channels, string message) {
    set<Client*> clients;
    for (map<string, Channel*>::iterator it = channels.begin();
         it != channels.end(); it++) {
        map<string, Client*> clientsMap = it->second->getClients();
        for (map<string, Client*>::iterator ut = clientsMap.begin();
             ut != clientsMap.end(); ut++) {
            clients.insert(ut->second);
        }
    }

    for (set<Client*>::iterator it = clients.begin(); it != clients.end(); it++)
        (*it)->sendMessage(message);
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

const char* Server::ClientNotFoundException::what() const throw() {
    return "Warning: Client was not found in the clients list";
}

const char* Server::ChannelNotFoundException::what() const throw() {
    return "Warning: Channel was not found in the channels list";
}
