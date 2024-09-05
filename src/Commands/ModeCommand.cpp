#include <sstream>
#include <stdexcept>

#include "Channel.hpp"
#include "Message.hpp"
#include "ModeCommand.hpp"
#include "Replies.hpp"
#include "Server.hpp"

using std::string;
using std::vector;

ModeCommand::ModeCommand(string source, vector<string> params, Client* client) {
    if (!client->isRegistered()) {
        client->sendMessage(Replies::ERR_NOTREGISTERED());
        throw ClientException();
    }

    if (params.size() < 1) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "MODE"));
        throw ClientException();
    }

    this->_target = params[0];

    if (_target[0] == '#') {
        this->_isChan = true;
        Channel* channel;
        try {
            channel = Server::getInstance().findChannel(_target);
        } catch (Server::ChannelNotFoundException&) {
            client->sendMessage(Replies::ERR_NOSUCHCHANNEL(client, _target));
            throw ClientException();
        }
        this->_channel = channel;
    } else {
        this->_isChan = false;
        Client* ctarget;
        try {
            ctarget = Server::getInstance().findClient(_target);
        } catch (Server::ClientNotFoundException&) {
            client->sendMessage(Replies::ERR_NOSUCHNICK(client, _target));
            throw ClientException();
        }
        if (ctarget != client) {
            client->sendMessage(Replies::ERR_USERSDONTMATCH(client));
            throw ClientException();
        }
    }

    this->_source = source;
    this->_params = params;
    this->_client = client;
    this->_modeExec = initMap();
    this->_mode = retrieveParam(params, 1);
}

ModeCommand::~ModeCommand() {}

string ModeCommand::retrieveParam(vector<string>& param, size_t i) {
    try {
        return param.at(i);
    } catch (std::out_of_range&) {
        return "";
    }
}

void ModeCommand::iModeDispatcher(bool oper, size_t& p) {
    if (_isChan)
        inviteMode(oper, p);
    else
        invisibleMode(oper, p);
}

void ModeCommand::invisibleMode(bool oper, size_t& p) {
    _client->setInvisible(oper);
    (void)p;
    addResult(oper, "i", "");
}

void ModeCommand::banMode(bool oper, size_t& p) {
    string param = retrieveParam(_params, p);
    if (param.empty()) {
        vector<Client*> banlist = _channel->getBanList();
        for (vector<Client*>::iterator it = banlist.begin();
             it != banlist.end(); it++)
            _client->sendMessage(Replies::RPL_BANLIST(_client, *it, _channel));
        _client->sendMessage(Replies::RPL_ENDOFBANLIST(_client, _channel));
        return;
    }

    p++;
    Client* target;
    try {
        target = Server::getInstance().findClient(param);
    } catch (Server::ClientNotFoundException&) {
        return;
    }
    if (oper) {
        _channel->banClient(target);
    } else
        _channel->unbanClient(target);
    addResult(oper, "b", param);
}

void ModeCommand::limitMode(bool oper, size_t& p) {
    if (!oper) {
        _channel->setMaxClients(0);
        addResult(oper, "l", "");
        return;
    }

    string param = retrieveParam(_params, p);
    if (param.empty())
        return;
    p++;
    std::stringstream ss(param);
    size_t limit;
    ss >> limit;

    _channel->setMaxClients(limit);
    addResult(oper, "l", param);
}

void ModeCommand::inviteMode(bool oper, size_t& p) {
    _channel->setInviteOnly(oper);
    (void)p;
    addResult(oper, "i", "");
}

void ModeCommand::keyMode(bool oper, size_t& p) {
    if (!oper) {
        _channel->clearKey();
        return;
    }

    string param = retrieveParam(_params, p);
    if (param.empty()) {
        _client->sendMessage(Replies::ERR_INVALIDKEY(_client, _channel));
        return;
    }

    p++;
    _channel->setKey(param);
    addResult(oper, "k", param);
}

void ModeCommand::moderatedMode(bool oper, size_t& p) {
    _channel->setModerated(oper);
    (void)p;
    addResult(oper, "m", "");
}

void ModeCommand::noExternalMode(bool oper, size_t& p) {
    _channel->setNoExternal(oper);
    (void)p;
    addResult(oper, "n", "");
}

void ModeCommand::protectedTopicMode(bool oper, size_t& p) {
    _channel->setProtectedTopic(oper);
    (void)p;
    addResult(oper, "t", "");
}

void ModeCommand::operatorMode(bool oper, size_t& p) {
    string param = retrieveParam(_params, p);
    if (param.empty())
        return;
    p++;

    Client* target;
    try {
        target = Server::getInstance().findClient(param);
    } catch (Server::ClientNotFoundException&) {
        return;
    }

    if (!_channel->isInChannel(target))
        return;

    if (oper)
        _channel->addOperator(target);
    else
        _channel->removeOperator(target);
    addResult(oper, "o", param);
}

void ModeCommand::voiceMode(bool oper, size_t& p) {
    string param = retrieveParam(_params, p);
    if (param.empty())
        return;
    p++;

    Client* target;
    try {
        target = Server::getInstance().findClient(param);
    } catch (Server::ClientNotFoundException&) {
        return;
    }

    if (!_channel->isInChannel(target))
        return;

    if (oper)
        _channel->addVoiced(target);
    else
        _channel->removeVoiced(target);
    addResult(oper, "v", param);
}

void ModeCommand::addResult(bool oper, string mode, string param) {
    if (oper)
        _modeResult += "+" + mode;
    else
        _modeResult += "-" + mode;

    if (!param.empty())
        _paramResult += " " + param;
}

void ModeCommand::run() {
    if (_isChan) {
        if (_mode.empty()) {
            _client->sendMessage(Replies::RPL_CHANNELMODEIS(_client, _channel));
            _client->sendMessage(Replies::RPL_CREATIONTIME(_client, _channel));
            return;
        }

        if (!_channel->isOperator(_client) && _mode != "b") {
            _client->sendMessage(
                Replies::ERR_CHANOPRIVSNEEDED(_client, _channel));
            return;
        }

    } else {
        if (_mode.empty()) {
            _client->sendMessage(Replies::RPL_UMODEIS(_client));
            return;
        }
    }

    executeMode();
}

void ModeCommand::executeMode() {
    if (_mode[0] != '-' && _mode[0] != '+' && _mode.size() > 1 &&
        _mode[1] != 'b') {
        _client->sendMessage(Replies::ERR_UMODEUNKNOWNFLAG(_client));
        return;
    }

    bool oper = true;
    bool unknownFlag = false;
    size_t p = 2;
    for (string::iterator it = _mode.begin(); it != _mode.end(); it++) {
        if (*it == '+' || *it == '-') {
            oper = *it == '+';
            continue;
        }
        if (_modeExec.find(*it) == _modeExec.end())
            unknownFlag = true;
        else
            (this->*_modeExec[*it])(oper, p);
    }

    if (unknownFlag)
        _client->sendMessage(Replies::ERR_UMODEUNKNOWNFLAG(_client));

    string message = ":" + _client->getNickname() + " MODE " + _params[0];
    message += " " + _modeResult + _paramResult;
    if (_isChan)
        Server::getInstance().sendMessage(_channel, Message::create(message),
                                          NULL);
    else
        _client->sendMessage(Message::create(message));
}