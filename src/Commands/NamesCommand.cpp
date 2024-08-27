#include "NamesCommand.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include <string>

NamesCommand::NamesCommand(std::string source, std::vector<std::string> params,
                           Client* client) {
    if (params.size() > 0) {
        this->_params[0] = params[0];
    } else {
        this->_params[0] = "";
    }
    this->_source = source;
    this->_client = client;
}

NamesCommand::~NamesCommand(){};

void NamesCommand::run() {
    if (_params[0].empty()) {

    } else {
        std::vector<std::string> channels = split(_params[0], ',');
        Channel* currChannel;
        for (std::vector<std::string>::iterator it = channels.begin();
             it != channels.end(); ++it) {
            try {
                currChannel = Server::getInstance().findChannel(*it);
                _client->sendMessage(
                    Replies::RPL_NAMREPLY(_client, currChannel));
            } catch (Server::ChannelNotFoundException()) {
                _client->sendMessage(Replies::RPL_ENDOFNAMES(_client, *it));
                continue;
            }
            _client->sendMessage(
                Replies::RPL_ENDOFNAMES(_client, currChannel->getName()));
        }
    }
    return;
}
/*
je loop selon les virgules dans _channels, pour chaque channel je liste les
clients, pour chaque client je check si il a ope ou
*/

/*
Channel map operator, la get et voir si client et dedans
Creer une map dans channel qui doit s’appeler voiceqqch
Get celle la aussi pour voir si voice
*/

/*
NAMES sans rien server::getclient et filtrer tous les user invisible
*/