#include "Channel.hpp"

Channel::Channel(Client* newClient, std::string name)
    : _name(name), _key(""), _protectedTopic(false), _inviteOnly(false),
      _maxClients(0) {
    checkNameSyntaxChan(name);
    this->_clients[newClient->getNickname()] = newClient;
    this->_operatorsList[newClient->getNickname()] = newClient;
}

Channel::Channel(Client* newClient, std::string name, std::string key)
    : _name(name), _key(key), _protectedTopic(false), _inviteOnly(false),
      _maxClients(0) {
    checkNameSyntaxChan(name);
    this->_clients[newClient->getNickname()] = newClient;
    this->_operatorsList[newClient->getNickname()] = newClient;
}

Channel::~Channel() {}

void Channel::checkNameSyntaxChan(std::string& name) {
    if (name[0] != '#')
        throw wrongSyntaxChannelName();
    if (name.find(' ') != name.npos)
        throw wrongSyntaxChannelName();
    if (name.find(0x07) != name.npos)
        throw wrongSyntaxChannelName();
    if (name.find(',') != name.npos)
        throw wrongSyntaxChannelName();
}

std::string const& Channel::getName() const { return this->_name; }

std::string Channel::getKey() const { return this->_key; }

void Channel::setKey(std::string newKey) { this->_key = newKey; }

void Channel::clearKey() { this->_key = ""; }

bool Channel::isKeyed() const { return !this->_key.empty(); }

std::string Channel::getTopic() const { return this->_topic; }

void Channel::setTopic(std::string newTopic) { this->_topic = newTopic; }

bool Channel::isProtectedTopic() const { return this->_protectedTopic; }

void Channel::setProtectedTopic(bool lock) { this->_protectedTopic = lock; }

std::map<std::string, Client*>& Channel::getClients() { return this->_clients; }

std::map<std::string, Client*>& Channel::getInvitelist() {
    return this->_inviteList;
}

std::map<std::string, Client*>& Channel::getBanList() { return this->_banList; }

std::map<std::string, Client*>& Channel::getOperatorsList() {
    return this->_operatorsList;
}

std::map<std::string, Client*>& Channel::getVoicedList() {
    return this->_voicedList;
}

bool Channel::isInviteOnly() const { return this->_inviteOnly; }

void Channel::setInviteOnly(bool inviteMode) { this->_inviteOnly = inviteMode; }

size_t Channel::getMaxClients() const { return this->_maxClients; }

void Channel::setMaxClients(size_t nbMaxClients) {
    this->_maxClients = nbMaxClients;
}

void Channel::addClient(Client* client) {
    if (this->_inviteOnly == true && !isInvited(client))
        throw userNotInvited();
    std::string nickname = client->getNickname();
    if (_clients.find(nickname) != _clients.end()) {
        throw userAlreadyExists();
    }
    _clients[nickname] = client;
}

void Channel::addOperator(Client* client) {
    addClientToMap(_operatorsList, client);
}

void Channel::addVoiced(Client* client) { addClientToMap(_voicedList, client); }

void Channel::banClient(Client* client) { addClientToMap(_banList, client); }

void Channel::inviteClient(Client* client) {
    addClientToMap(_inviteList, client);
}

void Channel::kickOperator(Client* client) {
    removeClientFromMap(_operatorsList, client, "the user was not an operator");
}

void Channel::eraseClient(Client* client) {
    removeClientFromMap(_clients, client, "the user does not exist");
}

void Channel::unbanClient(Client* client) {
    removeClientFromMap(_banList, client, "the user was not blacklisted");
}

bool Channel::isInChannel(Client* client) const {
    return (verifClientOnMap(_clients, client));
}

bool Channel::isInvited(Client* client) const {
    return (verifClientOnMap(_inviteList, client));
}

bool Channel::isBanned(Client* client) const {
    return (verifClientOnMap(_banList, client));
}

bool Channel::isOperator(Client* client) const {
    return (verifClientOnMap(_operatorsList, client));
}

bool Channel::isVoiced(Client* client) const {
    return (verifClientOnMap(_voicedList, client));
}

bool Channel::isInChannel(std::string nickname) const {
    return (verifClientOnMap(_clients, nickname));
}

bool Channel::isInvited(std::string nickname) const {
    return verifClientOnMap(_inviteList, nickname);
}

bool Channel::isBanned(std::string nickname) const {
    return (verifClientOnMap(_banList, nickname));
}

bool Channel::isOperator(std::string nickname) const {
    return (verifClientOnMap(_operatorsList, nickname));
}

std::string Channel::getModes() const {
    std::string modes = "+";

    if (isInviteOnly())
        modes += "i";
    if (isProtectedTopic())
        modes += "t";
    if (isKeyed())
        modes += "k";
    if (getMaxClients() > 1)
        modes += "l";
    return modes;
}

std::string Channel::getPrefix(Client* client) {
    std::string prefix = "+";
    if (this->isOperator(client))
        prefix += "o";
    if (this->isVoiced(client))
        prefix += "v";
    if (prefix == "+")
        prefix = "";
    return prefix;
}