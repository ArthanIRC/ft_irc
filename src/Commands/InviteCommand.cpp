#include "InviteCommand.hpp"

InviteCommand::InviteCommand(std::string source,
                             std::vector<std::string> params, Client* client) {
    if (!source.empty()) {
        throw std::invalid_argument("PASS command should not have a prefix.");
    }
    if (params.size() != 2) {
        throw std::invalid_argument(
            "INVITE command requires exactly two parameter.");
    }

    std::string nickname = params[0];
    std::string channel = params[1];
    if (channel[0] != '#' && channel[0] != '&') {
        throw std::invalid_argument("Channel name must start with '#' or '&'.");
    }
    this->_nickname = nickname;
    this->_channel = channel;
    // rajouter un check pour voir si le channel/user exist

    this->_client = client;
}

InviteCommand::~InviteCommand(){};

void InviteCommand::run() { return; }