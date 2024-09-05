#pragma once

#include <ctime>
#include <string>
#include <vector>

#include "Client.hpp"
#include "Exception.hpp"

class Channel {
  private:
    std::string _name;
    std::string _key;
    std::string _topic;
    std::string _lastTopicAuthor;
    bool _protectedTopic;
    bool _inviteOnly;
    bool _moderated;
    bool _noExternal;
    size_t _maxClients;
    time_t _creationTime;
    time_t _topicSetTime;
    std::vector<Client*> _clients;
    std::vector<Client*> _inviteList;
    std::vector<Client*> _banList;
    std::vector<Client*> _operatorsList;
    std::vector<Client*> _voicedList;
    void checkNameSyntax(std::string& name);

    void addClientToList(std::vector<Client*>& vec, Client* client);
    void removeClientFromList(std::vector<Client*>& vec, Client* client);
    bool isOnList(const std::vector<Client*>& vec, const Client* client) const;
    bool isOnList(const std::vector<Client*>& vec,
                  const std::string nickname) const;

  public:
    Channel(Client* client, std::string name);
    Channel(Client* newClient, std::string name, std::string key);
    ~Channel();

    std::string const& getName() const;

    std::string getKey() const;
    void setKey(std::string newKey);
    void clearKey();
    bool isKeyed() const;

    std::string getTopic() const;
    void setTopic(std::string newTopic, Client* author);
    bool isProtectedTopic() const;
    void setProtectedTopic(bool lock);

    std::vector<Client*>& getClients();
    std::vector<Client*>& getInvitelist();
    std::vector<Client*>& getBanList();
    std::vector<Client*>& getOperatorsList();
    std::vector<Client*>& getVoicedList();

    bool isInviteOnly() const;
    void setInviteOnly(bool inviteMode);

    bool isModerated() const;
    void setModerated(bool flag);

    bool isNoExternal() const;
    void setNoExternal(bool flag);

    size_t getMaxClients(void) const;
    void setMaxClients(size_t nbMaxClients);

    void addClient(Client* client);
    void addOperator(Client* client);
    void addVoiced(Client* client);
    void removeVoiced(Client* client);
    void banClient(Client* client);
    void inviteClient(Client* client);

    void removeOperator(Client* client);
    void unbanClient(Client* client);
    void removeClient(Client* client);

    bool isInChannel(Client* client) const;
    bool isInvited(Client* client) const;
    bool isBanned(Client* client) const;
    bool isOperator(Client* client) const;
    bool isVoiced(Client* client) const;
    bool isInChannel(std::string nickname) const;
    bool isInvited(std::string nickname) const;
    bool isBanned(std::string nickname) const;
    bool isOperator(std::string nickname) const;

    std::string getModes() const;
    std::string getPrefix(Client* client);
    std::string getLastTopicAuthor() const;
    time_t getCreationTime() const;
    time_t getTopicSetTime() const;

    class UserNotInvited : public ClientException {
      public:
        virtual const char* what() const throw() {
            return ("Error: The user is not invited.");
        }
    };

    class UserAlreadyExists : public ClientException {
      public:
        virtual const char* what() const throw() {
            return ("Error: The user already exists.");
        }
    };

    class WrongSyntaxChannelName : public ClientException {
      public:
        virtual const char* what() const throw() {
            return ("Error: Wrong syntax for channel name");
        }
    };
};
