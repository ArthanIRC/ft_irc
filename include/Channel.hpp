#pragma once

#include "Client.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <map>

class Channel {
  private:
    std::string _name;
    std::string _password;
    bool _inviteOnly;
    std::map<std::string, Client*> _clientsChan;
    std::map<std::string, Client*> _whiteList;
    std::map<std::string, Client*> _blackList;
    std::map<std::string, Client*> _operatorList;
    Channel();
    size_t _maxClients;
    // variable, struct ou class topic ?
  public:
    Channel(Client* newClient, std::string name, std::string password);
    ~Channel();
    std::string const& getName() const;
    std::map<std::string, Client*>& getClientsChan();
    bool getInviteOnly() const;
    void setInviteOnly(bool inviteMode);
    size_t getMaxClients(void) const;
    void setMaxClients(size_t nbMaxClients);
    void addClient(Client& client);
    void checkNameSyntaxChan(std::string& name);
    void eraseClient(Client &client);
    bool isInvited(Client &client);
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