#include "PassCommand.hpp"
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
    if (params[0] != Server::getInstance().getPassword()) {
        client->sendMessage(Replies::ERR_PASSWDMISMATCH());
        throw;
    }
};

PassCommand::~PassCommand(){};

void PassCommand::run() { return; }

/*
donc :
si la commande pass a un mot de passe correct, je modifie le state du client
pour qu'il aie PASS_DONE, et c'est tout si le serveur n'az aucun mot de passe,
je fais rien si le mot de passe est invalide, je retourne la numeric reply si
l'utilisateur n'a pas le state UNKNOWN; je retourne la numeric reply s'il manque
des params, je retourne la numeric reply
*/