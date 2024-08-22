#include "TopicCommand.hpp"
#include "Server.hpp"

TopicCommand::TopicCommand(std::string source, std::vector<std::string> params,
                           Client* client) {
    checkParams(client, params);
    this->_source = source;
    this->_params = params;
    this->_client = client;
}

void checkParams(Client* client, std::vector<std::string> params) {
    if (params.size() == 0) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS());
        throw();
    }
    try {
        Server::getInstance().findChannel(params[1]);
    } catch (const std::exception& e) {
        client->sendMessage(Replies::ERR_NOSUCHCHANNEL());
    }
}