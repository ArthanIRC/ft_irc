#include "Client.hpp"
#include "ClientSocket.hpp"

Client::Client(int fd)
    : _realname(""), _nickname(""), _username(""), _socket(fd), _state(UNKNOWN),
      _invisible(false) {}

Client::~Client() {}

std::string const& Client::getName() const { return this->_realname; }

std::string const& Client::getNickname() const { return this->_nickname; }

State Client::getState() const { return this->_state; }

ClientSocket& Client::getSocket() { return this->_socket; }

void Client::setState(State newState) { this->_state = newState; }

bool Client::isRegistered() { return this->_state >= REGISTERED; }

bool Client::isServerOperator() { return this->_state == OPERATOR; }

bool Client::isInvisible() { return this->_invisible; }

void Client::setInvisible(bool state) { this->_invisible = state; }

void Client::sendMessage(std::string message) { (void)message; }

std::string Client::getModes() {
    std::string modes = "+";

    if (isRegistered())
        modes += "r";
    if (isServerOperator())
        modes += "o";
    if (isInvisible())
        modes += "i";
    return modes;
}

// void Client::checkNameSyntaxCli(std::string nickname) {
//     if (nickname[0] == '#' || nickname[0] == '&' || nickname[0] == '+' ||
//         nickname[0] == '%')
//         throw std::runtime_error("Error syntax nickname");
//     if (nickname[0] == ':' || nickname[0] == '$')
//         throw std::runtime_error("Error syntax nickname");
//     if (nickname.find(' ') != nickname.npos)
//         throw std::runtime_error("Error syntax nickname");
//     if (nickname.find('*') != nickname.npos)
//         throw std::runtime_error("Error syntax nickname");
//     if (nickname.find('?') != nickname.npos)
//         throw std::runtime_error("Error syntax nickname");
//     if (nickname.find('.') != nickname.npos)
//         throw std::runtime_error("Error syntax nickname");
//     if (nickname.find(',') != nickname.npos)
//         throw std::runtime_error("Error syntax nickname");
//     if (nickname.find('!') != nickname.npos)
//         throw std::runtime_error("Error syntax nickname");
//     if (nickname.find('@') != nickname.npos)
//         throw std::runtime_error("Error syntax nickname");
// }