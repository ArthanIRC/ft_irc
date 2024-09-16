#include <algorithm>
#include <cctype>

#include "Client.hpp"
#include "NickCommand.hpp"
#include "Replies.hpp"
#include "Server.hpp"

using std::string;
using std::vector;

const static string ALLOWED_CHARS = "{}[]\\|";

static inline bool isInvalidNick(char c) {
    return !std::isalnum(c) && ALLOWED_CHARS.find(c) == string::npos;
}

NickCommand::NickCommand(string source, vector<string> params, Client* client) {
    if (params.size() < 1) {
        client->sendMessage(Replies::ERR_NONICKNAMEGIVEN(client));
        throw ClientException();
    }

    if (!Server::getInstance().getPassword().empty() &&
        client->getState() < PASS_DONE) {
        throw RegFailedException();
    }

    string nick = toLowerCase(params[0]);

    if (find_if(nick.begin(), nick.end(), isInvalidNick) != nick.end()) {
        client->sendMessage(Replies::ERR_ERRONEUSNICKNAME(client, nick));
        throw ClientException();
    }
    if (isNicknameUsed(nick)) {
        client->sendMessage(Replies::ERR_NICKNAMEINUSE(client, nick));
        throw ClientException();
    }

    this->_nick = nick;
    this->_source = source;
    this->_params = params;
    this->_client = client;
}

NickCommand::~NickCommand() {}

bool NickCommand::isNicknameUsed(string& nick) {
    vector<Client*> clients = Server::getInstance().getClients();
    for (vector<Client*>::iterator it = clients.begin(); it != clients.end();
         it++) {
        if ((*it)->getNickname() == nick)
            return true;
    }
    return false;
}

void NickCommand::run() {
    if (_client->isRegistered()) {
        string message = ":" + _client->getSource() + " NICK " + _nick;
        _client->setNickname(_nick);
        _client->sendMessage(Message::create(message));
        Server::getInstance().sendMessage(_client->getChannels(),
                                          Message::create(message), _client);
    }

    if (_client->getState() <= PASS_DONE) {
        _client->setNickname(_nick);
        _client->setState(NICK_DONE);
    }
}