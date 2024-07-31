#pragma once

#include "Client.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

class Channel {
  private:
    Channel();
    std::string _name;
    std::string _password;
    std::string _topic;
    bool _modifTopicByOps;
    bool _inviteOnly;
    size_t _maxClients;
    std::map<std::string, Client*> _clientsChan;
    std::map<std::string, Client*> _whiteList;
    std::map<std::string, Client*> _blackList;
    std::map<std::string, Client*> _operatorList;

    template <typename MapType>
    void addClientToMap(MapType& map, Client& client,
                        const std::string& errorMsg) {
        std::string nickname = client.getNickname();
        if (map.find(nickname) != map.end()) {
            throw std::runtime_error(errorMsg);
        }
        map[nickname] = &client;
    }

    template <typename MapType>
    void removeClientFromMap(MapType& map, Client& client,
                             const std::string& errorMsg) {
        std::string nickname = client.getNickname();
        typename MapType::iterator it = map.find(nickname);
        if (it != map.end()) {
            map.erase(it);
        } else {
            throw std::runtime_error(errorMsg);
        }
    }

    template <typename MapType>
    bool verifClientOnMap(const MapType& map, const Client& client) const {
        std::string nickname = client.getNickname();
        typename MapType::const_iterator it = map.find(nickname);
        return it != map.end();
    }

  public:
    Channel(Client* client, std::string name);
    Channel(Client* newClient, std::string name, std::string password);
    ~Channel();

    void checkNameSyntaxChan(std::string& name);
    std::string const& getName() const;

    std::string getPassword() const;
    void setPassword(std::string newPassword);
    void clearPassword();

    std::string getTopic() const;
    void setTopic(std::string newTopic);
    bool getModifTopicByOps() const;
    void setModifTopicByOps(bool lock);

    std::map<std::string, Client*>& getClientsChan();
    std::map<std::string, Client*>& getWhitelist();
    std::map<std::string, Client*>& getBlacklist();
    std::map<std::string, Client*>& getOperatorlist();

    bool getInviteOnly() const;
    void setInviteOnly(bool inviteMode);

    size_t getMaxClients(void) const;
    void setMaxClients(size_t nbMaxClients);

    void addClient(Client& client);
    void addOperator(Client& client);
    void banClient(Client& client);

    void kickOperator(Client& client);
    void debanClient(Client& client);
    void eraseClient(Client& client);

    bool isWhitelisted(Client& client) const;
    bool isBlacklisted(Client& client) const;
    bool isOperator(Client& client) const;

    std::string getChannelMode() const;

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
    // KICK: ejecter un user
    // MODE : changer les mode du chan
    // INVITE : inviter un user sur le chan sur invitation
    // TOPIC : changer le sujet du chan

    // '+' ajoute les modes qui suivent et '-' les supprimes
    // '+t'
};
