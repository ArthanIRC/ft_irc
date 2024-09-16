#include <climits>
#include <cstdlib>
#include <sstream>

#include "Bot.hpp"
#include "Message.hpp"
#include "Server.hpp"

using std::string;
using std::vector;

static const string defaultPort = "6667";

Bot::Bot() {}

Bot::~Bot() {}

void Bot::init(int ac, char** data) {
    if (ac < 3 || ac > 4)
        throw Bot::InvalidNumberOfParametersException();

    string port;
    if (ac == 3)
        port = defaultPort;
    else
        port = Server::parsePort(data[3]);

    this->_password = Server::parsePassword(data[2]);
    this->_running = true;
    this->_registered = false;
    this->_socket.init(data[1], port.c_str());
}

void Bot::run() {
    this->_socket.connect();

    while (_running) {
        if (!_registered) {
            login();
        }
        string data = _socket.receive();
        if (data.empty() && _socket.isEof())
            break;
        if (data.empty())
            continue;

        vector<string> message = parse(data);
        execute(message);
    }
}

int Bot::roll(int min, int max) {
    double x = rand() / static_cast<double>(INT_MIN);

    int result = min + static_cast<int>(x * (max - min));
    return result;
}

void Bot::execute(vector<string> message) {
    string source = message.at(0);
    string command = message.at(1);
    string target = message.at(2);
    string param = message.at(3);

    if (command == "PRIVMSG") {
        if (param.find("/joke") == 0)
            joke(source, target);
        else
            imDad(source, target, param);
    }
}

void Bot::imDad(string source, string target, string content) {
    string lowerContent = toLowerCase(content);
    size_t pos = lowerContent.find("i'm");

    if (pos == string::npos || (pos + 4) > content.size())
        return;
    string rem = content.substr(pos + 4);
    string joke = "Hi " + rem + ", I'm Dad !";

    if (target == _nickname)
        target = source.substr(source.find(":"), source.find("!"));

    string reply = "PRIVMSG " + target + " :" + joke + "\r\n";
    _socket.sendMessage(reply);
}

void Bot::joke(string source, string target) {
    if (target == _nickname)
        target = source.substr(source.find(":"), source.find("!"));

    string joke;
    if (_jokes.empty())
        joke = "Sowwwy, I'm too dumb to read the joke file, no jokes "
               "for uuwu. \\(>w<)/\"";
    else
        joke = _jokes.at(roll(0, _jokes.size() - 1));
    string reply = "PRIVMSG " + target + " :" + joke + "\r\n";
    _socket.sendMessage(reply);
}

string Bot::joinPara(vector<string>& splitData) {
    std::ostringstream messageStream;

    for (std::size_t i = 3; i < splitData.size(); ++i) {
        if (i != 3)
            messageStream << " ";
        messageStream << splitData[i];
    }
    return messageStream.str();
}

vector<string> Bot::parse(string& data) {
    vector<string> splitData = Message::split(data, ' ');

    if (splitData.size() >= 4) {
        std::string parameter = joinPara(splitData);
        splitData.resize(4);
        splitData[3] = parameter;
    }

    return splitData;
}

void Bot::login() {}

void Bot::stop() { this->_running = false; }

Bot& Bot::getInstance() {
    static Bot instance;
    return instance;
}

const char* Bot::InvalidNumberOfParametersException::what() const throw() {
    return "Error: Usage: ./ircbot <address> <password> [<port>]";
}

const char* Bot::InvalidPortException::what() const throw() {
    return "Error: Port has to be between 1 and 65535";
}