#include "PassCommand.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <cctype>

PassCommand::PassCommand(std::string source, std::vector<std::string> params,
                         Client* client) {
    if (params.size() < 1) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "PASS"));
        throw;
    }
    if (!source.empty()) {
        throw;
    }
    this->_client = client;
    this->_password = params[0];
};

PassCommand::~PassCommand(){};

void PassCommand::run() {
    if (_password != Server::getInstance().getPassword()) {
        client->sendMessage(Replies::ERR_PASSWDMISMATCH());
        throw;
    }
    if (_client->getState() != UNKNOWN) {
        client->sendMessage(Replies::ERR_ALREADYREGISTERED());
        throw;
    }
    _client->setState(PASS_DONE);
    return;
}

/*
donc :
si la commande pass a un mot de passe correct, je modifie le state du client
pour qu'il aie PASS_DONE, et c'est tout si le serveur n'az aucun mot de passe,
je fais rien si le mot de passe est invalide, je retourne la numeric reply si
l'utilisateur n'a pas le state UNKNOWN; je retourne la numeric reply s'il manque
des params, je retourne la numeric reply
*/