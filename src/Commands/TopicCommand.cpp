#include "TopicCommand.hpp"
#include "Replies.hpp"
#include "Server.hpp"

using std::string;
using std::vector;

TopicCommand::TopicCommand(string source, vector<string> params,
                           Client* client) {
    checkParams(client, params);
    this->_source = source;
    this->_params = params;
    this->_client = client;
}

TopicCommand::~TopicCommand() {}

void TopicCommand::checkParams(Client* client, vector<string> params) {
    if (!client->isRegistered()) {
        client->sendMessage(Replies::ERR_NOTREGISTERED());
        throw ClientException();
    }
    if (params.size() == 0) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "TOPIC"));
        throw ClientException();
    }

    Channel* chan;
    try {
        chan = Server::getInstance().findChannel(params[0]);
    } catch (const Server::ChannelNotFoundException&) {
        client->sendMessage(Replies::ERR_NOSUCHCHANNEL(client, params[0]));
        throw ClientException();
    }

    this->_channel = chan;
    if (!(chan->isInChannel(client))) {
        client->sendMessage(Replies::ERR_NOTONCHANNEL(client, chan));
        throw ClientException();
    }

    if (params.size() > 1 && chan->isProtectedTopic()) {
        if (!chan->isOperator(client)) {
            client->sendMessage(Replies::ERR_CHANOPRIVSNEEDED(client, chan));
            throw ClientException();
        }
    }
}

void TopicCommand::run() {
    if (_params.size() < 2) {
        if (_channel->getTopic().empty())
            _client->sendMessage(Replies::RPL_NOTOPIC(_client, _channel));
        else {
            _client->sendMessage(Replies::RPL_TOPIC(_client, _channel));
            _client->sendMessage(Replies::RPL_TOPICWHOTIME(_client, _channel));
        }
    } else {
        _channel->setTopic(_params[1], _client);
        string message = ":" + _client->getSource() + " TOPIC " +
                         _channel->getName() + " :" + _params[1];
        Server::getInstance().sendMessage(_channel, Message::create(message),
                                          NULL);
    }
}