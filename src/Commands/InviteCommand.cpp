#include "InviteCommand.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include <exception>

InviteCommand::InviteCommand(std::string source,
                             std::vector<std::string> params, Client* client) {
    Channel* chan;
    try {
        chan = Server::getInstance().findChannel(params[1]);
    } catch (const std::exception& e) {
        client->sendMessage(Replies::ERR_NOSUCHCHANNEL());
        throw();
    }
    if (!chan->isInChannel(*client)) {
        client->sendMessage(Replies::ERR_NOTONCHANNEL());
        throw();
    }
    if (chan->getInviteOnly() && !chan->isOperator(*client)) {
        client->sendMessage(Replies::ERR_CHANOPRIVSNEEDED());
        throw();
    }
    if (chan->isInChannel(params[0])) {
        client->sendMessage(Replies::ERR_USERONCHANNEL());
        throw();
    }
}

InviteCommand::~InviteCommand(){};

void InviteCommand::run() { return; }