#include "PassCommand.hpp"

PassCommand::PassCommand(std::string prefix, std::vector<std::string> params) {
    if (!prefix.empty()) {
        throw std::invalid_argument("PASS command should not have a prefix.");
    }
    if (params.size() != 1) {
        throw std::invalid_argument(
            "PASS command requires exactly one parameter.");
    }
    this->_password = params[0];

    if (_password.empty()) {
        throw std::invalid_argument("Password cannot be empty.");
    }
    for (std::string::iterator it = _password.begin(); it != _password.end();
         ++it) {
        if (!std::isprint(*it) || std::isspace(*it)) {
            throw std::invalid_argument(
                "Password contains invalid characters.");
        }
    }
};

PassCommand::~PassCommand(){};

void PassCommand::run() { return; }