#include "WhoCommand.hpp"

WhoCommand::WhoCommand(std::string source, std::vector<std::string> params,
                       Client* client) {
    checkParams(client, params);
    this->_source = source;
    this->_params = params;
    this->_client = client;
}