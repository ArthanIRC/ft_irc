#include <algorithm>

#include "Channel.hpp"

using std::string;
using std::vector;

Channel::Channel(Client* newClient, string name)
    : _name(name), _key(""), _protectedTopic(false), _inviteOnly(false),
      _noExternal(true), _maxClients(0) {
    checkNameSyntax(name);
    this->_clients.push_back(newClient);
    this->_operatorsList.push_back(newClient);
    this->_creationTime = time(NULL);
}

Channel::Channel(Client* newClient, string name, string key)
    : _name(name), _key(key), _protectedTopic(false), _inviteOnly(false),
      _noExternal(true), _maxClients(0) {
    checkNameSyntax(name);
    this->_clients.push_back(newClient);
    this->_operatorsList.push_back(newClient);
    this->_creationTime = time(NULL);
}

Channel::~Channel() {}

void Channel::checkNameSyntax(string& name) {
    if (name[0] != '#')
        throw WrongSyntaxChannelName();
    if (name.find(' ') != name.npos)
        throw WrongSyntaxChannelName();
    if (name.find(0x07) != name.npos)
        throw WrongSyntaxChannelName();
    if (name.find(',') != name.npos)
        throw WrongSyntaxChannelName();
}

void Channel::addClientToList(vector<Client*>& vec, Client* client) {
    if (std::find(vec.begin(), vec.end(), client) != vec.end())
        return;
    vec.push_back(client);
}

void Channel::removeClientFromList(vector<Client*>& vec, Client* client) {
    vector<Client*>::iterator it = std::find(vec.begin(), vec.end(), client);
    if (it != vec.end())
        vec.erase(it);
}

bool Channel::isOnList(const vector<Client*>& vec, const Client* client) const {
    vector<Client*>::const_iterator it =
        std::find(vec.begin(), vec.end(), client);
    return it != vec.end();
}

bool Channel::isOnList(const vector<Client*>& vec,
                       const string nickname) const {
    for (vector<Client*>::const_iterator it = vec.begin(); it != vec.end();
         it++) {
        if ((*it)->getNickname() == nickname)
            return true;
    }
    return false;
}

string const& Channel::getName() const { return this->_name; }

string Channel::getKey() const { return this->_key; }

void Channel::setKey(string newKey) { this->_key = newKey; }

void Channel::clearKey() { this->_key = ""; }

bool Channel::isKeyed() const { return !this->_key.empty(); }

string Channel::getTopic() const { return this->_topic; }

void Channel::setTopic(string newTopic, Client* author) {
    this->_topic = newTopic;
    this->_lastTopicAuthor = author->getNickname();
    this->_topicSetTime = time(NULL);
}

bool Channel::isProtectedTopic() const { return this->_protectedTopic; }

void Channel::setProtectedTopic(bool lock) { this->_protectedTopic = lock; }

vector<Client*>& Channel::getClients() { return this->_clients; }

vector<Client*>& Channel::getInvitelist() { return this->_inviteList; }

vector<Client*>& Channel::getBanList() { return this->_banList; }

vector<Client*>& Channel::getOperatorsList() { return this->_operatorsList; }

vector<Client*>& Channel::getVoicedList() { return this->_voicedList; }

bool Channel::isInviteOnly() const { return this->_inviteOnly; }

void Channel::setInviteOnly(bool inviteMode) { this->_inviteOnly = inviteMode; }

bool Channel::isModerated() const { return this->_moderated; }

void Channel::setModerated(bool flag) { this->_moderated = flag; }

bool Channel::isNoExternal() const { return this->_noExternal; }

void Channel::setNoExternal(bool flag) { this->_noExternal = flag; }

size_t Channel::getMaxClients() const { return this->_maxClients; }

void Channel::setMaxClients(size_t nbMaxClients) {
    this->_maxClients = nbMaxClients;
}

void Channel::addClient(Client* client) {
    if (this->_inviteOnly == true && !isInvited(client))
        throw UserNotInvited();
    addClientToList(_clients, client);
}

void Channel::addOperator(Client* client) {
    addClientToList(_operatorsList, client);
}

void Channel::addVoiced(Client* client) {
    addClientToList(_operatorsList, client);
}

void Channel::removeVoiced(Client* client) {
    removeClientFromList(_voicedList, client);
}

void Channel::banClient(Client* client) { addClientToList(_banList, client); }

void Channel::inviteClient(Client* client) {
    addClientToList(_inviteList, client);
}

void Channel::removeOperator(Client* client) {
    removeClientFromList(_operatorsList, client);
}

void Channel::removeClient(Client* client) {
    removeClientFromList(_clients, client);
}

void Channel::unbanClient(Client* client) {
    removeClientFromList(_banList, client);
}

bool Channel::isInChannel(Client* client) const {
    return isOnList(_clients, client);
}

bool Channel::isInvited(Client* client) const {
    return isOnList(_inviteList, client);
}

bool Channel::isBanned(Client* client) const {
    return isOnList(_banList, client);
}

bool Channel::isOperator(Client* client) const {
    return isOnList(_operatorsList, client) || client->isServerOperator();
}

bool Channel::isVoiced(Client* client) const {
    return isOperator(client) || isOnList(_voicedList, client);
}

bool Channel::isInChannel(string nickname) const {
    return isOnList(_clients, nickname);
}

bool Channel::isInvited(string nickname) const {
    return isOnList(_inviteList, nickname);
}

bool Channel::isBanned(string nickname) const {
    return isOnList(_banList, nickname);
}

bool Channel::isOperator(string nickname) const {
    return isOnList(_operatorsList, nickname);
}

string Channel::getModes() const {
    string modes = "+";

    if (!_banList.empty())
        modes += "b";
    if (isInviteOnly())
        modes += "i";
    if (isKeyed())
        modes += "k";
    if (getMaxClients() > 1)
        modes += "l";
    if (isModerated())
        modes += "m";
    if (isNoExternal())
        modes += "n";
    if (isProtectedTopic())
        modes += "t";

    return modes;
}

string Channel::getPrefix(Client* client) {
    string prefix = "";
    if (this->isOperator(client))
        prefix += "@";
    else if (this->isVoiced(client))
        prefix += "+";
    return prefix;
}

string Channel::getLastTopicAuthor() const { return this->_lastTopicAuthor; }

time_t Channel::getCreationTime() const { return this->_creationTime; }

time_t Channel::getTopicSetTime() const { return this->_topicSetTime; }