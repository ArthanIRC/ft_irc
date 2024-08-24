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

std::map<std::string, Client*>& Channel::getInvitelist() {
    return (this->_invitelist);
}

std::map<std::string, Client*>& Channel::getBanlist() {
    return (this->_banlist);
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
    if (this->_inviteOnly == true && !isInvited(client))
        throw userNotInvited();
    std::string nickname = client.getNickname();
    if (_clientsChan.find(nickname) != _clientsChan.end()) {
        throw userAlreadyExists();
    }
    _clientsChan[nickname] = &client;
}

void Channel::addOperator(Client& client) {
    addClientToMap(_operatorList, client);
}

void Channel::banClient(Client& client) { addClientToMap(_banlist, client); }

void Channel::inviteClient(Client& client) {
    addClientToMap(_invitelist, client);
}

void Channel::kickOperator(Client& client) {
    removeClientFromMap(_operatorList, client, "the user was not an operator");
}

void Channel::eraseClient(Client& client) {
    removeClientFromMap(_clientsChan, client, "the user does not exist");
}

void Channel::debanClient(Client& client) {
    removeClientFromMap(_banlist, client, "the user was not blacklisted");
}

bool Channel::isInChannel(Client& client) const {
    return (verifClientOnMap(_clientsChan, client));
}

bool Channel::isInvited(Client& client) const {
    return (verifClientOnMap(_invitelist, client));
}

bool Channel::isBanned(Client& client) const {
    return (verifClientOnMap(_banlist, client));
}

bool Channel::isOperator(Client& client) const {
    return (verifClientOnMap(_operatorList, client));
}

bool Channel::isInChannel(std::string nickname) const {
    return (verifClientOnMap(_clientsChan, nickname));
}

bool Channel::isInvited(std::string nickname) const {
    return verifClientOnMap(_invitelist, nickname);
}

bool Channel::isBanned(std::string nickname) const {
    return (verifClientOnMap(_banlist, nickname));
}

bool Channel::isOperator(std::string nickname) const {
    return (verifClientOnMap(_operatorList, nickname));
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
