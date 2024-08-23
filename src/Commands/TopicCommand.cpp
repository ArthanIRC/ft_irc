#include "TopicCommand.hpp"
#include "Replies.hpp"
#include "Server.hpp"

TopicCommand::TopicCommand(std::string source, std::vector<std::string> params,
                           Client* client) {
    checkParams(client, params);
    this->_source = source;
    this->_params = params;
    this->_client = client;
}

TopicCommand::~TopicCommand() {}

void TopicCommand::checkParams(Client* client,
                               std::vector<std::string> params) {
    if (params.size() == 0) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS());
        throw;
    }
    Channel* chan;
    try {
        chan = Server::getInstance().findChannel(params[0]);
    } catch (const std::exception& e) {
        client->sendMessage(Replies::ERR_NOSUCHCHANNEL());
        throw;
    }
    this->_channel = chan;
    if (!(chan->isInChannel(*client))) {
        client->sendMessage(Replies::ERR_NOTONCHANNEL());
        throw;
    }
    if (params.size() > 1 && chan->getModifTopicByOps()) {
        if (!chan->isOperator(*client)) {
            client->sendMessage(Replies::ERR_CHANOPRIVSNEEDED());
            throw;
        }
    }
}

void TopicCommand::run() {
    if (this->_params.size() < 2) {
        this->_client->sendMessage(Replies::RPL_TOPIC());
    } else {
        std::map<std::string, Client*> clientMap =
            this->_channel->getClientsChan();
        std::map<std::string, Client*>::iterator it;
        this->_channel->setTopic(this->_params[1]);
        for (it = clientMap.begin(); it != clientMap.end(); ++it) {
            (*it).second->sendMessage(Replies::RPL_TOPIC());
            (*it).second->sendMessage(Replies::RPL_TOPICWHOTIME());
        }
    }
}