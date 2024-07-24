#pragma once

#include "Client.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Channel {
  private:
    std::string _name;
    std::string _password;
    bool _inviteOnly;
    std::vector<Client*> _clientsChan;
    Channel();
    // variable, struct ou class topic ? avec nom du topic, si il est modif il
    // faut avertir tt les user du chan
  public:
    Channel(Client* newClient, std::string name, std::string password);
    ~Channel();
    std::string const& getName() const;
    std::vector<Client*>& getClientsChan();
    bool getInviteOnly() const;
    void setInviteOnly(bool inviteMode);
    void addClient(Client& client);
    void checkNameSyntaxChan(std::string& name);
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