#include "InviteCommand.hpp"
#include "Channel.hpp"
#include <exception>

InviteCommand::InviteCommand(std::string source,
                             std::vector<std::string> params, Client* client) {
    Channel* chan;
    try {
        chan = Server::getInstance().findChannel(params[0]);
    } catch (const std::exception& e) {
        client->sendMessage(Replies::ERR_NOSUCHCHANNEL());
    }
    try {
        chan->;
    } catch (const std::exception& e) {
        client->sendMessage(Replies::ERR_NOTONCHANNEL());
    }
}

InviteCommand::~InviteCommand(){};

void InviteCommand::run() { return; }

/*
Only members of the channel are allowed to invite other users. Otherwise, the
server MUST reject the command with the ERR_NOTONCHANNEL numeric.
*/