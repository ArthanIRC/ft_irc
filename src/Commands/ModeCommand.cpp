#include "ModeCommand.hpp"
#include "Server.hpp"

ModeCommand::ModeCommand(std::string source, std::vector<std::string> params,
                         Client* client) {
    if (params.size() < 1) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS());
        throw;
    }
    std::string target = params[0];

    this->_source = source;
    this->_params = params;
    this->_client = client;
    if (target[0] == '#')
        throw;
}

ModeCommand::~ModeCommand() {}

void ModeCommand::run() {}