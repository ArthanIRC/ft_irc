#include "Channel.hpp"

Channel::Channel(Client* newClient, std::string name, std::string password)
    : _name(name), _password(password), _inviteOnly(false), _maxClients(0) {
    checkNameSyntaxChan(name);
    this->_clientsChan[newClient->getNickname()] = newClient;
    this->_operatorList[newClient->getNickname()] = newClient;
}

Channel::~Channel() { 
    _clientsChan.clear();
    _operatorList.clear(); 
}

std::string const& Channel::getName() const { return (this->_name); }

std::map<std::string, Client*>& Channel::getClientsChan() { return (this->_clientsChan); }

bool Channel::getInviteOnly() const { return (this->_inviteOnly); }

void Channel::setInviteOnly(bool inviteMode) { this->_inviteOnly = inviteMode; }

size_t Channel::getMaxClients() const { return (this->_maxClients); }

void Channel::setMaxClients(size_t nbMaxClients) { this->_maxClients = nbMaxClients; }

void Channel::addClient(Client& client) {
    if (this->_inviteOnly == true && !isInvited(client))
        throw std::runtime_error("the user is not invited");
    std::string nickname = client.getNickname();
    if (_clientsChan.find(nickname) != _clientsChan.end()) {
        throw std::runtime_error("the user already exists");
    }
    _clientsChan[nickname] = &client;
}

void Channel::eraseClient(Client &client) {
    std::string nickname = client.getNickname();
    std::map<std::string, Client*>::iterator it = _clientsChan.find(nickname);
    if (it != _clientsChan.end())
        _clientsChan.erase(it);
    else
        throw std::runtime_error("the user does not exist");
}

bool Channel::isInvited(Client &client) {
    std::string nickname = client.getNickname();
    std::map<std::string, Client*>::iterator it = _whiteList.find(nickname);
    if (it != _whiteList.end())
        return true;
    return false;
}

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