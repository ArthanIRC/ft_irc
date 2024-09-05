#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <locale>
#include <sstream>
#include <vector>

#include "Message.hpp"
#include "Server.hpp"

using std::string;
using std::vector;

Message::~Message() {}

bool Message::verify(string& data) {
    string source, command;
    vector<string> params;
    int res = Message::parse(data, source, command, params);

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
    if (Message::validate(source, command, params) == false) {
        throw(Message::InvalidFormatException());
    }

    return (true);
}

int Message::parse(string& data, string& source, string& command,
                   vector<string>& params) {
    if (data.length() < 2 || data.substr(data.length() - 2) != "\r\n") {
        return (err_trailing);
    }
    data = data.substr(0, data.length() - 2);
    if (data.find('\n') != string::npos || data.find('\r') != string::npos) {
        return (err_newline);
    }

    std::istringstream iss(data);
    string word;

    if (data[0] == ':') {
        iss >> word;
        source = word.substr(1);
    }

    if (!(iss >> command)) {
        return (err_missing_cmd);
    }

    while (iss >> word) {
        if (word[0] == ':') {
            string trailing;
            getline(iss, trailing);
            word.erase(0, 1);
            word += trailing;
            params.push_back(word);
            break;
        }
        if (word.find(':') != string::npos) {
            return (err_trailing);
        }
        params.push_back(word);
    }

    std::transform(command.begin(), command.end(), command.begin(), ::toupper);

    return (0);
}

bool Message::validate(const string& source, const string& command,
                       const vector<string>& params) {

    std::locale loc("en_US.UTF-8");

    if (!source.empty()) {
        for (size_t i = 0; i < source.length(); ++i) {
            if (!std::isalnum(source[i]) && source[i] != '-' &&
                source[i] != '.' && source[i] != '!' && source[i] != '@') {
                return (false);
            }
        }
    }

    if (command.empty()) {
        return (false);
    }

    for (string::const_iterator it = command.begin(); it != command.end();
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
            if (!std::isprint(params[i][j], loc)) {
                return (false);
            }
        }
    }

    return (true);
}

vector<string> Message::split(string& str, char delim) {
    std::istringstream iss(str);
    string buffer;
    vector<string> result;

    while (std::getline(iss, buffer, delim))
        result.push_back(buffer);

    return result;
}

string Message::create(string& data) {
    if (data[0] != ':') {
        data = ":" + Server::getInstance().getSource() + " " + data;
    }

    return data += "\r\n";
}