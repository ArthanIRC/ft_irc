#include "Channel.hpp"

Channel::Channel(Client* newClient, std::string name)
    : _name(name), _password(""), _modifTopicByOps(false), _inviteOnly(false),
      _maxClients(0) {
    checkNameSyntaxChan(name);
    this->_clientsChan[newClient->getNickname()] = newClient;
    this->_operatorList[newClient->getNickname()] = newClient;
}

Channel::Channel(Client* newClient, std::string name, std::string password)
    : _name(name), _password(password), _modifTopicByOps(false),
      _inviteOnly(false), _maxClients(0) {
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
        throw wrongSyntaxChannelName();
    if (name.find(' ') != name.npos)
        throw wrongSyntaxChannelName();
    if (name.find(0x07) != name.npos)
        throw wrongSyntaxChannelName();
    if (name.find(',') != name.npos)
        throw wrongSyntaxChannelName();
}

std::string const& Channel::getName() const { return (this->_name); }

std::string Channel::getPassword() const { return (this->_password); }

void Channel::setPassword(std::string newPassword) {
    this->_password = newPassword;
}

void Channel::clearPassword() { this->_password = ""; }

std::string Channel::getTopic() const { return (this->_topic); }

void Channel::setTopic(std::string newTopic) { this->_topic = newTopic; }

bool Channel::getModifTopicByOps() const { return (this->_modifTopicByOps); }

void Channel::setModifTopicByOps(bool lock) { this->_modifTopicByOps = lock; }

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
        throw userNotInvited();
    std::string nickname = client.getNickname();
    if (_clientsChan.find(nickname) != _clientsChan.end()) {
        throw userAlreadyExists();
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

bool Channel::isInChannel(Client& client) const {
    if (verifClientOnMap(_clientsChan, client))
        return (true);
    return (false);
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

bool Channel::isInChannel(std::string nickname) const {
    if (verifClientOnMap(_clientsChan, nickname))
        return (true);
    return (false);
}

bool Channel::isWhitelisted(std::string nickname) const {
    if (verifClientOnMap(_whiteList, nickname))
        return (true);
    return (false);
}

bool Channel::isBlacklisted(std::string nickname) const {
    if (verifClientOnMap(_blackList, nickname))
        return (true);
    return (false);
}

bool Channel::isOperator(std::string nickname) const {
    if (verifClientOnMap(_operatorList, nickname))
        return (true);
    return (false);
}

std::string Channel::getChannelMode() const {
    std::string mode = "+";

    if (getInviteOnly())
        mode += "i";
    if (getModifTopicByOps())
        mode += "t";
    if (!_password.empty())
        mode += "k";
    if (getMaxClients() > 1)
        mode += "l";
    return (mode);
}