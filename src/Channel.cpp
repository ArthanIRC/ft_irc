#include "Channel.hpp"

Channel::Channel(Client* newClient, std::string name, std::string password)
    : _name(name), _password(password), _inviteOnly(false) {
    checkNameSyntaxChan(name);
    this->_clientsChan.push_back(newClient);
}

Channel::~Channel() { _clientsChan.clear(); }

std::string const& Channel::getName() const { return (this->_name); }

std::vector<Client*>& Channel::getClientsChan() { return (this->_clientsChan); }

bool Channel::getInviteOnly() const { return (this->_inviteOnly); }

void Channel::setInviteOnly(bool inviteMode) { this->_inviteOnly = inviteMode; }

/*void Channel::addClient(Client& client) {
    if (std::find(_clientsChan.begin(), _clientsChan.end(), client) !=
        _clientsChan.end())
        throw std::runtime_error("the user already exist");
    this->_clientsChan.push_back(&client);
} */

void Channel::checkNameSyntaxChan(std::string& name) {
    if (name[0] != '#')
        throw std::runtime_error("Error syntax name");
    if (name.find(' ') != name.npos)
        throw std::runtime_error("Error syntax name");
    if (name.find(0x07) != name.npos)
        throw std::runtime_error("Error syntax name");
    if (name.find(',') != name.npos)
        throw std::runtime_error("Error syntax name");
}