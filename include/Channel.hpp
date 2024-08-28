#pragma once

#include <map>
#include <stdexcept>
#include <string>

#include "Client.hpp"

class Channel {
  private:
    std::string _name;
    std::string _key;
    std::string _topic;
    bool _protectedTopic;
    bool _inviteOnly;
    bool _moderated;
    size_t _maxClients;
    std::map<std::string, Client*> _clients;
    std::map<std::string, Client*> _inviteList;
    std::map<std::string, Client*> _banList;
    std::map<std::string, Client*> _operatorsList;
    std::map<std::string, Client*> _voicedList;
    void checkNameSyntaxChan(std::string& name);

    template <typename MapType>
    void addClientToMap(MapType& map, Client* client) {
        std::string nickname = client->getNickname();
        if (map.find(nickname) != map.end()) {
            return;
        }
        map[nickname] = client;
    }

    template <typename MapType>
    void removeClientFromMap(MapType& map, Client* client,
                             const std::string& errorMsg) {
        std::string nickname = client->getNickname();
        typename MapType::iterator it = map.find(nickname);
        if (it != map.end()) {
            map.erase(it);
        } else {
            throw std::runtime_error(errorMsg);
        }
    }

    template <typename MapType>
    bool verifClientOnMap(const MapType& map, const Client* client) const {
        std::string nickname = client->getNickname();
        typename MapType::const_iterator it = map.find(nickname);
        return it != map.end();
    }

    template <typename MapType>
    bool verifClientOnMap(const MapType& map,
                          const std::string nickname) const {
        typename MapType::const_iterator it = map.find(nickname);
        return it != map.end();
    }

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
    void setTopic(std::string newTopic);
    bool isProtectedTopic() const;
    void setProtectedTopic(bool lock);

    std::map<std::string, Client*>& getClients();
    std::map<std::string, Client*>& getInvitelist();
    std::map<std::string, Client*>& getBanList();
    std::map<std::string, Client*>& getOperatorsList();
    std::map<std::string, Client*>& getVoicedList();

    bool isInviteOnly() const;
    void setInviteOnly(bool inviteMode);

    bool isModerated() const;
    void setModerated(bool flag);

    size_t getMaxClients(void) const;
    void setMaxClients(size_t nbMaxClients);

    void addClient(Client* client);
    void addOperator(Client* client);
    void addVoiced(Client* client);
    void banClient(Client* client);
    void inviteClient(Client* client);

    void eraseOperator(Client* client);
    void unbanClient(Client* client);
    void eraseClient(Client* client);

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

    class userNotInvited : public std::exception {
      public:
        virtual const char* what() const throw() {
            return ("Error: The user is not invited.");
        }
    };

    class userAlreadyExists : public std::exception {
      public:
        virtual const char* what() const throw() {
            return ("Error: The user already exists.");
        }
    };

    class wrongSyntaxChannelName : public std::exception {
      public:
        virtual const char* what() const throw() {
            return ("Error: Wrong syntax for channel name");
        }
    };
};
