#include "JoinCommand.hpp"
#include <sstream>
#include <vector>

JoinCommand::JoinCommand(std::string source, std::vector<std::string> params,
                         Client* client) {
    checkParams(client, params);
    this->_source = source;
    this->_params = params;
    this->_client = client;
}

JoinCommand::~JoinCommand() {}

void JoinCommand::checkParams(Client* client, std::vector<std::string> params) {
    if (params.size() < 1) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "JOIN"));
        throw;
    }
    setLists(client, params);
}

void JoinCommand::setLists(Client* client, std::vector<std::string> params) {
    std::istringstream iss(params[0]);
    std::istringstream iss2(params[1]);
    std::string tmp;
    size_t i = 0;
    size_t j = 0;

    while (std::getline(iss, tmp, ',')) {
        try {
            _chanlist[i] = Server::getInstance().findChannel(tmp);
        } catch (const Server::ChannelNotFoundException()) {
            client->sendMessage(Replies::ERR_NOSUCHCHANNEL(client, tmp));
            throw;
        }
        i++;
    }
    while (std::getline(iss2, _keylist[j], ','))
        j++;
}

void JoinCommand::run() { return; }