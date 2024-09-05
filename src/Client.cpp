#include "Client.hpp"
#include "ClientSocket.hpp"
#include "Server.hpp"

using std::map;
using std::string;

Client::Client(int fd)
    : _realname(""), _nickname(""), _username(""), _socket(fd), _state(UNKNOWN),
      _capEndedEarly(false), _invisible(false), _away(false),
      _awayNotify(false) {}

Client::~Client() {
    map<string, Channel*> channels = getChannels();
    if (channels.empty())
        return;

    for (map<string, Channel*>::iterator it = channels.begin();
         it != channels.end(); it++)
        it->second->removeClient(this);
}

string const& Client::getNickname() const { return this->_nickname; }

string const& Client::getUserName() const { return this->_username; }

string const& Client::getRealName() const { return this->_realname; }

string const Client::getSource() const {
    string source = _nickname + "!" + _username + "@localhost";
    return source;
}

string const& Client::getAwayMsg() const { return this->_awayMsg; }

State Client::getState() const { return this->_state; }

ClientSocket& Client::getSocket() { return this->_socket; }

void Client::setState(State newState) { this->_state = newState; }

bool Client::hasCapEndedEarly() { return this->_capEndedEarly; }

bool Client::isRegistered() { return this->_state >= REGISTERED; }

bool Client::isServerOperator() { return this->_state == OPERATOR; }

bool Client::isAway() { return this->_away; }

bool Client::isAwayNotify() { return this->_awayNotify; }

bool Client::isInvisible() { return this->_invisible; }

void Client::setCapEndedEarly() { this->_capEndedEarly = true; }

void Client::setAway(bool state, string message) {
    this->_away = state;
    this->_awayMsg = message;
}

void Client::setAwayNotify(bool state) { this->_awayNotify = state; }

void Client::setInvisible(bool state) { this->_invisible = state; }

void Client::setNickname(string& nick) { this->_nickname = nick; }

void Client::setUsername(string& username) { this->_username = username; }

void Client::setRealname(string& realname) { this->_realname = realname; }

void Client::sendMessage(string message) { _socket.sendMessage(message); }

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
    map<string, Channel*> result;
    for (map<string, Channel*>::iterator it = servMap.begin();
         it != servMap.end(); it++) {
        if (it->second->isInChannel(this))
            result[it->first] = it->second;
    }

    return result;
}