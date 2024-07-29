#include "../include/Message.hpp"
#include <cstddef>
#include <cstdio>
#include <sstream>

Message::~Message() {}

#include <iostream>
void Message::create(std::string& data) {
    std::string prefix, command;
    std::vector<std::string> params;
    int res = Message::parse(data, prefix, command, params);

    switch (res) {
    case (0):
        break;
    case (1001):
        throw(Message::WrongTrailingException());
        break;
    case (1002):
        throw(Message::NewlineException());
        break;
    case (1003):
        throw(Message::MissingCommandException());
        break;
    default:
        throw(Message::UnknownErrorException());
        break;
    }

    // for (size_t i = 0; i < params.size(); ++i) {
    //     std::cout << params[i] << std::endl;
    // }
    if (Message::validate(prefix, command, params) == false) {
        throw(Message::InvalidFormatException());
    }

    // ici message valide donc appel de commande etc
}

int Message::parse(std::string& data, std::string& prefix, std::string& command,
                   std::vector<std::string>& params) {
    if (data.length() < 2 || data.substr(data.length() - 2) != "\r\n") {
        return (err_trailing);
    }
    data = data.substr(0, data.length() - 2);
    if (data.find('\n') != std::string::npos ||
        data.find('\r') != std::string::npos) {
        return (err_newline);
    }

    std::istringstream iss(data);
    std::string word;

    if (data[0] == ':') {
        iss >> word;
        prefix = word.substr(1);
    }

    if (!(iss >> command)) {
        return (err_missing_cmd);
    }

    while (iss >> word) {
        std::cout << "@@ " << word << std::endl;
        if (word[0] == ':') {
            std::string trailing;
            getline(iss, trailing);
            word.erase(0, 1);
            word += trailing;
            params.push_back(word);
            break;
        }
        std::cout << "@@@@@ " << word << std::endl;
        if (word.find(':') != std::string::npos) {
            std::cout << "@@@@@@@ " << word << std::endl;
            return (err_trailing);
        }
        params.push_back(word);
    }
    return (0);
}

bool Message::validate(const std::string& prefix, const std::string& command,
                       const std::vector<std::string>& params) {
    if (!prefix.empty()) {
        for (size_t i = 0; i < prefix.length(); ++i) {
            if (!std::isalnum(prefix[i]) && prefix[i] != '-' &&
                prefix[i] != '.' && prefix[i] != '!' && prefix[i] != '@') {
                return (false);
            }
        }
    }

    if (command.empty()) {
        return (false);
    }

    for (std::string::const_iterator it = command.begin(); it != command.end();
         ++it) {
        if (!std::isupper(*it) && !std::isdigit(*it)) {
            return (false);
        }
    }

    if (params.size() > max_params) {
        return (false);
    }

    for (size_t i = 0; i < params.size(); ++i) {
        for (size_t j = 0; j < params[i].length(); ++j) {
            if (!std::isprint(params[i][j])) {
                return (false);
            }
        }
    }

    // if (!params.empty()) {
    //     std::string last_param = params[params.size() - 1];
    //     std::cout << "@@@@@@@@ " << last_param << std::endl;
    //     if (!last_param.empty() && last_param[0] == ':') {
    //         std::cout << "test" << std::endl;
    //         // The trailing parameter should be the last one
    //         if (params.size() > 1) {
    //             // Ensure there is a space before the trailing parameter
    //             std::string second_last_param = params[params.size() - 2];
    //             if (second_last_param.empty() ||
    //                 second_last_param[second_last_param.length() - 1] == ':')
    //                 { return false; // Trailing parameter should be preceded
    //                 by a
    //                               // space, not a colon
    //             }
    //         }
    //     }
    // }

    return (true);
}