#include "Client.hpp"

Client::Client(std::string nickname)
    : _realname(NULL), _nickname(nickname), _username(NULL), _fd(-1) {
    checkNameSyntaxCli(nickname);
}

Client::~Client() {}

std::string const& Client::getName() const { return (this->_realname); }

std::string const& Client::getNickname() const { return (this->_nickname); }

int const& Client::getFd() const { return (this->_fd); }

void Client::setFd(int& fd) { this->_fd = fd; }

void Client::checkNameSyntaxCli(std::string nickname) {
    if (nickname[0] == '#' || nickname[0] == '&' || nickname[0] == '+' ||
        nickname[0] == '%')
        throw std::runtime_error("Error syntax nickname");
    if (nickname[0] == ':' || nickname[0] == '$')
        throw std::runtime_error("Error syntax nickname");
    if (nickname.find(' ') != nickname.npos)
        throw std::runtime_error("Error syntax nickname");
    if (nickname.find('*') != nickname.npos)
        throw std::runtime_error("Error syntax nickname");
    if (nickname.find('?') != nickname.npos)
        throw std::runtime_error("Error syntax nickname");
    if (nickname.find('.') != nickname.npos)
        throw std::runtime_error("Error syntax nickname");
    if (nickname.find(',') != nickname.npos)
        throw std::runtime_error("Error syntax nickname");
    if (nickname.find('!') != nickname.npos)
        throw std::runtime_error("Error syntax nickname");
    if (nickname.find('@') != nickname.npos)
        throw std::runtime_error("Error syntax nickname");
}