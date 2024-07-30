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
    std::string topic;
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
    bool verifClientOnMap(MapType& map, Client& client) const {
      std::string nickname = client.getNickname();
    typename MapType::iterator it = map.find(nickname);
    if (it != map.end())
        return true;
    return false;
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
    // KICK: ejecter un user
    // MODE : changer les mode du chan
    // INVITE : inviter un user sur le chan sur invitation (bool _inviteOnly =
    // true?) TOPIC : changer le sujet du chan

    /* dans les modes il y a :	-ban(liste des clients qui peuvent pas join ou
    parler) -InviteOnly (si le channel est accessible uniquement par invitation)
                                                            -ClientLimit (il y a
    un nombre max de user dans le chan et si il y a un JOIN il faut verif si le
    chan est full) -InvitException (liste de clients qui peuvent join sans invit
    meme en mode invitOnly) -Keymode (pour rejoindre le chan il faut une clef,
    si elle est fausse il peut pas rejoindre le chan) les modes sont
    reconnaissables avec des prefixes mis devant le nickname de l'utilisateur.
  */
};
