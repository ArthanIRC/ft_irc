#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <set>

#include "Channel.hpp"
#include "Client.hpp"
#include "Replies.hpp"
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
static const string source = "arthan@justice.42.fr";
static const string userModes = "ior";
static const string channelModes = "biklmnotv";
static const string version = "1.0.0";
static const string creationDate = "27/07/2024";
static const string rplSupport1 =
    "AWAYLEN=255 BOT=B CASEMAPPING=ascii CHANLIMIT=#: CHANMODES=b,k,l,imnt "
    "CHANNELLEN=30 CHANTYPES=# "
    "ELIST= HOSTLEN=64 KICKLEN=255 MAXLIST=b:20 NICKLEN=30 PREFIX=(ov)@+ ";
static const string rplSupport2 = "STATUSMSG= TOPICLEN=307 USERLEN=18";
static const string botKey = "#WM5dal&wGPoVR";

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

string Server::parsePort(const char* strp) {
    int port = strtol(strp, NULL, 10);

    if (port < 1 || port > 65535)
        throw Server::InvalidPortException();
    return strp;
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
    this->_maxClients = 0;
    this->_socket.init(_port.c_str());
    this->_running = true;
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

bool Server::isRunning() const { return this->_running; }

void Server::addClient(Client* c) {
    _clients.push_back(c);
    if (_clients.size() > _maxClients)
        _maxClients = _clients.size();
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

map<std::string, Channel*> Server::getChannels() { return this->_channels; }

map<std::string, std::string> Server::getOperators() {
    return this->_operators;
}

vector<Client*> Server::getClients() { return this->_clients; }

set<Client*> Server::getClientsSet(map<string, Channel*> channels,
                                   Client* sender) {
    set<Client*> clients;
    for (map<string, Channel*>::iterator it = channels.begin();
         it != channels.end(); it++) {
        vector<Client*> clientsVec = it->second->getClients();
        for (vector<Client*>::iterator ut = clientsVec.begin();
             ut != clientsVec.end(); ut++) {
            if (!sender || *ut != sender)
                clients.insert(*ut);
        }
    }

    return clients;
}

string Server::getBotKey() const { return botKey; }

string Server::getChannelModes() const { return channelModes; }

string Server::getCreationDate() const { return creationDate; }

string Server::getMotd() const { return motd; }

string Server::getNetworkName() const { return networkName; }

string Server::getPassword() const { return this->_password; }

string Server::getRplSupport1() const { return rplSupport1; }

string Server::getRplSupport2() const { return rplSupport2; }

string Server::getServerName() const { return serverName; }

std::string Server::getSource() { return source; }

string Server::getUserModes() const { return userModes; }

string Server::getVersion() const { return version; }

Epoll& Server::getEpoll() { return this->_epoll; }

size_t Server::getMaxClients() const { return _maxClients; }

void Server::sendMessage(Channel* channel, string message, Client* sender) {
    vector<Client*> clients = channel->getClients();
    for (vector<Client*>::iterator it = clients.begin(); it != clients.end();
         it++) {
        if (!sender || *it != sender)
            (*it)->sendMessage(message);
    }
}

void Server::sendMessage(map<string, Channel*> channels, string message,
                         Client* sender) {
    set<Client*> clients = getClientsSet(channels, sender);
    for (set<Client*>::iterator it = clients.begin(); it != clients.end(); it++)
        (*it)->sendMessage(message);
}

void Server::sendMessageIfAway(Channel* channel, string message,
                               Client* sender) {
    vector<Client*> clients = channel->getClients();
    for (vector<Client*>::iterator it = clients.begin(); it != clients.end();
         it++) {
        if ((!sender || *it != sender) && (*it)->isAwayNotify())
            (*it)->sendMessage(message);
    }
}

void Server::sendMessageIfAway(map<string, Channel*> channels, string message,
                               Client* sender) {
    set<Client*> clients = getClientsSet(channels, sender);
    for (set<Client*>::iterator it = clients.begin(); it != clients.end();
         it++) {
        if ((*it)->isAwayNotify())
            (*it)->sendMessage(message);
    }
}

void Server::notifyPrivBot(string chanName) {
    for (vector<Client*>::iterator it = _clients.begin(); it != _clients.end();
         it++) {
        if ((*it)->isServerOperator() && (*it)->isBot())
            (*it)->sendMessage(Replies::RPL_NEWCHAN(*it, chanName));
    }
}

Server& Server::getInstance() {
    static Server instance;
    return instance;
}

string toLowerCase(string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
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
