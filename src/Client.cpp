#include "Client.hpp"
#include "ClientSocket.hpp"

Client::Client(int fd)
    : _realname(""), _nickname(""), _username(""), _socket(fd),
      _state(UNKNOWN) {}

Client::~Client() {}

std::string const& Client::getName() const { return this->_realname; }

std::string const& Client::getNickname() const { return this->_nickname; }

State Client::getState() const { return this->_state; }

ClientSocket& Client::getSocket() { return this->_socket; }

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