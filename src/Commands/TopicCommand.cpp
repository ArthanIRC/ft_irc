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
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "TOPIC"));
        throw;
    }
    Channel* chan;
    try {
        chan = Server::getInstance().findChannel(params[0]);
    } catch (const Server::ChannelNotFoundException()) {
        client->sendMessage(Replies::ERR_NOSUCHCHANNEL(client, params[0]));
        throw;
    }
    this->_channel = chan;
    if (!(chan->isInChannel(*client))) {
        client->sendMessage(Replies::ERR_NOTONCHANNEL(client, chan));
        throw;
    }
    if (params.size() > 1 && chan->getModifTopicByOps()) {
        if (!chan->isOperator(*client)) {
            client->sendMessage(Replies::ERR_CHANOPRIVSNEEDED(client, chan));
            throw;
        }
    }
}

void TopicCommand::run() {
    if (_params.size() < 2) {
        _client->sendMessage(Replies::RPL_TOPIC(_client, _channel));
    } else {
        std::map<std::string, Client*> clientMap = _channel->getClientsChan();
        std::map<std::string, Client*>::iterator it;
        _channel->setTopic(_params[1]);

        for (it = clientMap.begin(); it != clientMap.end(); ++it) {
            (*it).second->sendMessage(Replies::RPL_TOPIC(_client, _channel));
            (*it).second->sendMessage(Replies::RPL_TOPICWHOTIME());
        }
    }
}