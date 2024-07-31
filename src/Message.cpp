#include "Message.hpp"
#include <cstddef>
#include <cstdio>
#include <sstream>

Message::~Message() {}

bool Message::verify(std::string& data) {
    std::string prefix, command;
    std::vector<std::string> params;
    int res = Message::parse(data, prefix, command, params);

    switch (res) {
    case (0):
        break;
    case (err_trailing):
        throw(Message::WrongTrailingException());
        break;
    case (err_newline):
        throw(Message::NewlineException());
        break;
    case (err_missing_cmd):
        throw(Message::MissingCommandException());
        break;
    default:
        throw(Message::UnknownErrorException());
        break;
    }
    if (Message::validate(prefix, command, params) == false) {
        throw(Message::InvalidFormatException());
    }

    return (true);
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
        if (word[0] == ':') {
            std::string trailing;
            getline(iss, trailing);
            word.erase(0, 1);
            word += trailing;
            params.push_back(word);
            break;
        }
        if (word.find(':') != std::string::npos) {
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

    return (true);
}