#include "ModeCommand.hpp"
#include "Channel.hpp"
#include "Replies.hpp"
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
            client->sendMessage(Replies::ERR_NOSUCHCHANNEL(client, _target));
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

void ModeCommand::setInvisible(bool oper) {
    std::string mode;

    if (oper)
        mode = "+i";
    else
        mode = "-i";

    std::string nickname = _client->getNickname();
    _client->setInvisible(oper);
    _client->sendMessage(":" + nickname + "MODE " + nickname + mode);
}

void ModeCommand::userMode() {
    if (_mode.empty()) {
        _client->sendMessage(Replies::RPL_UMODEIS(_client));
        return;
    }

    if (_mode[0] != '-' && _mode[0] != '+') {
        _client->sendMessage(Replies::ERR_UMODEUNKNOWNFLAG(_client));
        return;
    }

    bool unknownFlag = false;
    bool oper;
    for (std::string::iterator it = _mode.begin(); it != _mode.end(); it++) {
        if (*it == '-')
            oper = false;
        else if (*it == '+')
            oper = true;
        else if (*it == 'i')
            setInvisible(oper);
        else
            unknownFlag = true;
    }

    if (unknownFlag)
        _client->sendMessage(Replies::ERR_UMODEUNKNOWNFLAG(_client));
}

void ModeCommand::chanMode() {}