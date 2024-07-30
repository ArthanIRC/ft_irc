#include "Channel.hpp"

Channel::Channel(Client* newClient, std::string name)
    : _name(name), _password(""), _inviteOnly(false), _maxClients(0) {
    checkNameSyntaxChan(name);
    this->_clientsChan[newClient->getNickname()] = newClient;
    this->_operatorList[newClient->getNickname()] = newClient;
}

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

std::string const& Channel::getName() const { return (this->_name); }

std::string Channel::getPassword() const {
    return (this->_password);
}

void Channel::setPassword(std::string newPassword) {
    this->_password = newPassword;
}

void Channel::clearPassword() {
    this->_password = "";
}

std::string Channel::getTopic() const {
    return (this->topic);
}

void Channel::setTopic(std::string newTopic) {
    this->topic = newTopic;
}

std::map<std::string, Client*>& Channel::getClientsChan() {
    return (this->_clientsChan);
}

std::map<std::string, Client*>& Channel::getWhitelist() {
    return (this->_whiteList);
}

std::map<std::string, Client*>& Channel::getBlacklist() {
    return (this->_blackList);
}

std::map<std::string, Client*>& Channel::getOperatorlist() {
    return (this->_operatorList);
}

bool Channel::getInviteOnly() const { return (this->_inviteOnly); }

void Channel::setInviteOnly(bool inviteMode) { this->_inviteOnly = inviteMode; }

size_t Channel::getMaxClients() const { return (this->_maxClients); }

void Channel::setMaxClients(size_t nbMaxClients) {
    this->_maxClients = nbMaxClients;
}

void Channel::addClient(Client& client) {
    if (this->_inviteOnly == true && !isWhitelisted(client))
        throw std::runtime_error("the user is not invited");
    std::string nickname = client.getNickname();
    if (_clientsChan.find(nickname) != _clientsChan.end()) {
        throw std::runtime_error("the user already exists");
    }
    _clientsChan[nickname] = &client;
}

void Channel::addOperator(Client& client) {
    addClientToMap(_operatorList, client, "the user is already an operator");
}

void Channel::banClient(Client& client) {
    addClientToMap(_operatorList, client, "the user is already an operator");
}

void Channel::kickOperator(Client& client) {
    removeClientFromMap(_operatorList, client, "the user was not an operator");
}

void Channel::eraseClient(Client& client) {
    removeClientFromMap(_clientsChan, client, "the user does not exist");
}

void Channel::debanClient(Client& client) {
    removeClientFromMap(_blackList, client, "the user was not blacklisted");
}

bool Channel::isWhitelisted(Client& client) const {
    if (verifClientOnMap(_whiteList, client))
        return (true);
    return (false);
}

bool Channel::isBlacklisted(Client& client) const {
    if (verifClientOnMap(_blackList, client))
        return (true);
    return (false);
}

bool Channel::isOperator(Client& client) const {
    if (verifClientOnMap(_operatorList, client))
        return (true);
    return (false);
}
