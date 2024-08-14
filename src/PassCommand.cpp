#include "PassCommand.hpp"

PassCommand::PassCommand(std::string prefix, std::vector<std::string> params) {
    if (!prefix.empty()) {
        throw std::invalid_argument("PASS command should not have a prefix.");
    }
    if (params.size() != 1) {
        throw std::invalid_argument(
            "PASS command requires exactly one parameter.");
    }
    std::string password = params[0];

    if (password.empty()) {
        throw std::invalid_argument("Password cannot be empty.");
    }
    for (std::string::iterator it = password.begin(); it != password.end();
         ++it) {
        if (!std::isprint(*it) || std::isspace(*it)) {
            throw std::invalid_argument(
                "Password contains invalid characters.");
        }
    }
    // this->password = password;
    // ou stocker le password ? je mets ca pour sen souvenir
};

PassCommand::~PassCommand(){};

void PassCommand::run() { return; }