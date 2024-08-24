#include "ModeCommand.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include <stdexcept>

ModeCommand::ModeCommand(std::string source, std::vector<std::string> params,
                         Client* client) {
    if (params.size() < 1) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "MODE"));
        throw;
    }

    this->_target = params[0];

    if (_target[0] == '#') {
        this->_chanTarget = true;
        Channel* channel;
        try {
            channel = Server::getInstance().findChannel(_target);
        } catch (Server::ChannelNotFoundException& e) {
            client->sendMessage(Replies::ERR_NOSUCHCHANNEL(client, channel));
            throw;
        }
        this->_channel = channel;
    } else {
        Client* ctarget;
        try {
            ctarget = Server::getInstance().findClient(_target);
        } catch (Server::ClientNotFoundException& e) {
            client->sendMessage(Replies::ERR_NOSUCHNICK(client, _target));
            throw;
        }
        if (ctarget != client) {
            client->sendMessage(Replies::ERR_USERSDONTMATCH(client));
            throw;
        }
    }

    this->_source = source;
    this->_params = params;
    this->_client = client;

    try {
        this->_mode = params.at(1);
    } catch (std::out_of_range& e) {
        this->_mode = "";
    }
}

ModeCommand::~ModeCommand() {}

void ModeCommand::run() {
    if (_chanTarget)
        chanMode();
    else
        userMode();
}

/*void ModeCommand::userMode() {
    if (_mode.empty())
        _client->sendMessage(Replies::RPL_UMODEIS(_client));
    else {

    }
} */