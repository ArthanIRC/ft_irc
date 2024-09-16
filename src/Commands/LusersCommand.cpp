#include "LusersCommand.hpp"
#include "Replies.hpp"

using std::string;
using std::vector;

LusersCommand::LusersCommand(string source, vector<string> params,
                             Client* client) {
    if (!client->isRegistered()) {
        client->sendMessage(Replies::ERR_NOTREGISTERED());
        throw ClientException();
    }

    this->_source = source;
    this->_params = params;
    this->_client = client;
}

LusersCommand::~LusersCommand() {}

void LusersCommand::run() {
    _client->sendMessage(Replies::RPL_LUSERCLIENT(_client));
    _client->sendMessage(Replies::RPL_LUSEROP(_client));
    _client->sendMessage(Replies::RPL_LUSERUNKNOWN(_client));
    _client->sendMessage(Replies::RPL_LUSERCHANNELS(_client));
    _client->sendMessage(Replies::RPL_LUSERME(_client));
    _client->sendMessage(Replies::RPL_LOCALUSERS(_client));
    _client->sendMessage(Replies::RPL_GLOBALUSERS(_client));
}