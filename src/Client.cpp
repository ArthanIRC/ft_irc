#include "Client.hpp"
#include "ClientSocket.hpp"
#include "Server.hpp"

using std::map;
using std::string;

Client::Client(int fd)
    : _realname(""), _nickname(""), _username(""), _socket(fd), _state(UNKNOWN),
      _invisible(false) {}

Client::~Client() {}

string const& Client::getName() const { return this->_realname; }

string const& Client::getNickname() const { return this->_nickname; }

string const Client::getSource() const {
    string source = _nickname + "!" + _username + "@localhost";
    return source;
}

State Client::getState() const { return this->_state; }

ClientSocket& Client::getSocket() { return this->_socket; }

void Client::setState(State newState) { this->_state = newState; }

bool Client::isRegistered() { return this->_state >= REGISTERED; }

bool Client::isServerOperator() { return this->_state == OPERATOR; }

bool Client::isInvisible() { return this->_invisible; }

void Client::setInvisible(bool state) { this->_invisible = state; }

void Client::setNickname(string& nick) { this->_nickname = nick; }

void Client::setUsername(string& username) { this->_username = username; }

void Client::setRealname(string& realname) { this->_realname = realname; }

void Client::sendMessage(string message) { (void)message; }

string Client::getModes() {
    string modes = "+";

    if (isRegistered())
        modes += "r";
    if (isServerOperator())
        modes += "o";
    if (isInvisible())
        modes += "i";
    return modes;
}

map<string, Channel*> Client::getChannels() {
    map<string, Channel*> servMap = Server::getInstance().getChannels();
    map<string, Channel*> result = servMap;
    for (map<string, Channel*>::iterator it = servMap.begin();
         it != servMap.end();) {
        if (it->second->isInChannel(this))
            ++it;
        else
            result.erase(it++);
    }

    return result;
}