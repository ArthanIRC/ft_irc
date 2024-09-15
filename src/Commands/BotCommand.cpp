#include "BotCommand.hpp"
#include "Client.hpp"
#include "Exception.hpp"
#include "JoinCommand.hpp"
#include <algorithm>
#include <vector>

using std::map;
using std::string;
using std::vector;

BotCommand::BotCommand(string source, vector<string> params, Client* client) {
    if (!client->isRegistered()) {
        client->sendMessage(Replies::ERR_NOTREGISTERED());
        throw ClientException();
    }

    if (params.empty()) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "BOT"));
        throw ClientException();
    }

    this->_source = source;
    this->_params = params;
    this->_client = client;
    this->_key = params[0];
}

BotCommand::~BotCommand() {}

// not sure about function placement etc
void BotCommand::imDad(string name) {
    if (_sender[0] == '#') { // check for segfault
        // send to chan
    } else {
        // send to self
    }
    std::cout << "Hi " + name + ", I'm Dad !" << std::endl; // tmp test
}

void BotCommand::joke() {
    if (_sender[0] == '#') { // check for segfault
        // send to chan
    } else {
        // send to self
    }
    std::cout << "You don’t need a parachute to go skydiving. You do need one "
                 "if you want to go skydiving twice."
              << std::endl; // tmp test
    // logic to get a joke from input file
}

// joins everything after target
string BotCommand::joinMessage(vector<string>& splitData) {
    std::ostringstream messageStream;

    for (std::size_t i = 3; i < splitData.size(); ++i) {
        if (i != 3)
            messageStream << " ";
        messageStream << splitData[i];
    }
    return messageStream.str();
}

void BotCommand::checkSender() {
    _sender = _source.substr(_source.find(":"), _source.find("!"));
}

void BotCommand::dadParse(string& data) {
    vector<string> splitData = split(data, ' ');
    _source = splitData.at(0);
    _target = splitData.at(2);

    if (splitData.size() >= 4) {
        std::string fullMessage = BotCommand::joinMessage(splitData);
        splitData.resize(4);
        splitData[3] = fullMessage;
    }
    checkSender();
    if (splitData.at(1) == "PRIVMSG") {
        string& message = splitData.at(3);

        if (message.find("/joke") == 0) {
            joke();
            return;
        }

        string lowerMessage = message;
        transform(lowerMessage.begin(), lowerMessage.end(),
                  lowerMessage.begin(), ::tolower);
        size_t pos = lowerMessage.find("i'm");

        if (pos != string::npos && (pos + 4) < message.size()) {
            string rest = message.substr(pos + 4);
            imDad(rest);
        }
    }
}

void BotCommand::run() {
    if (Server::getInstance().getBotKey() != _key) {
        _client->sendMessage(Replies::ERR_INVALIDBOTKEY(_client));
        return;
    }

    _client->setState(OPERATOR);
    _client->setBot(true);
    _client->sendMessage(Replies::RPL_YOUREOPER(_client));
    string reply = ":" + Server::getInstance().getSource() + " MODE " +
                   _client->getNickname() + " +Bo";
    _client->sendMessage(Message::create(reply));
    _client->sendMessage(Replies::RPL_YOUREPRIVBOT(_client));

    map<string, Channel*> channels = Server::getInstance().getChannels();
    string chansToJoin;
    for (map<string, Channel*>::iterator it = channels.begin();
         it != channels.end(); it++) {
        if (!chansToJoin.empty())
            chansToJoin += ",";
        chansToJoin += it->first;
    }

    vector<string> tmp;
    tmp.push_back(chansToJoin);
    JoinCommand j("", tmp, _client);
    j.run();
}