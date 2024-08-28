#include "OperCommand.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Replies.hpp"

OperCommand::OperCommand(std::string source, std::vector<std::string> params,
                         Client* client) {
    if (params.size() < 2) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "OPER"));
        throw;
    }
    this->_source = source;
    this->_client = client;
}

OperCommand::~OperCommand() {}

void OperCommand::run() {}