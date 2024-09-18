#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Bot.hpp"
#include "Exception.hpp"
#include "Message.hpp"
#include "Server.hpp"

using std::string;
using std::vector;

static const string defaultPort = "6667";
static const string dadFile = "bot/dad_jokes.txt";

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
    readFile();
}

void Bot::readFile() {
    std::fstream infile(dadFile.c_str(), std::fstream::in);
    string buffer;

    if (!infile) {
        std::cerr << "Error while opening the file " + dadFile << "\n";
        return;
    }

    while (std::getline(infile, buffer))
        this->_jokes.push_back(buffer);

    if (infile.bad()) {
        std::cerr << "Error while reading the file " + dadFile << "\n";
        this->_jokes.clear();
    }
}

int Bot::roll(int min, int max) {
    int n = max - min + 1;
    int rem = RAND_MAX % n;
    int x;
    do
        x = rand();
    while (x >= RAND_MAX - rem);
    return min + x % n;
}

string Bot::joinPara(vector<string>& splitData, size_t i) {
    std::ostringstream messageStream;

    for (size_t j = i; j < splitData.size(); j++) {
        if (j != i)
            messageStream << " ";
        messageStream << splitData[j];
    }
    return messageStream.str();
}

vector<string> Bot::parse(string& data) {
    vector<string> splitData = Message::split(data, ' ');

    if (splitData.size() > 1) {
        size_t i = 1;
        for (; i < splitData.size(); i++)
            if (splitData.at(i).find(':') != string::npos)
                break;
        if (i != splitData.size()) {
            std::string parameter = joinPara(splitData, i);
            splitData.resize(i + 1);
            if (parameter[0] == ':')
                parameter.erase(0, 1);
            splitData[i] = parameter;
        }
    }

    return splitData;
}

void Bot::run() {
    this->_socket.connect();

    while (_running) {
        if (!_registered)
            login();

        string data = _socket.receive();

        if (data.empty() && _socket.isEof())
            break;
        if (data.empty())
            continue;

        vector<string> message = parse(data);
        try {
            execute(message);
        } catch (BotSocket::SendException& e) {
            std::cerr << e.what() << "\n";
        }
    }
}

void Bot::login() {
    _socket.sendMessage("CAP LS 302\r\n");
    string data = _socket.receive();
    string rpl = "PASS " + _password +
                 "\r\nNICK daddy\r\nUSER Dad * * :Dad\r\nCAP END\r\n";
    _socket.sendMessage(rpl);
    data = _socket.receive();

    vector<string> message = Message::split(data, ' ');
    if (message.at(1) != "001")
        throw RegFailedException(data);
    this->_nickname = message.at(2);
    while (data.find("221") == string::npos) {
        data = _socket.receive();
        std::cout << data;
    }

    _socket.sendMessage("BOT #WM5dal&wGPoVR\r\n");
    data = _socket.receive();
    message = Message::split(data, ' ');
    if (message.at(1) != "910")
        throw RegFailedException();

    this->_registered = true;
    return;
}

void Bot::stop() { this->_running = false; }

Bot& Bot::getInstance() {
    static Bot instance;
    return instance;
}

void Bot::execute(vector<string> message) {
    string source = message.at(0);
    string command = message.at(1);
    string target = message.at(2);
    string param;

    try {
        param = message.at(3);
    } catch (std::out_of_range&) {
    }

    if (command == "PRIVMSG") {
        if (param.find("!joke") == 0)
            joke(source, target);
        else
            imDad(source, target, param);
    } else if (command == "911") {
        string joinRequest = "JOIN " + param + "\r\n";
        _socket.sendMessage(joinRequest);
    }
}

void Bot::imDad(string source, string target, string content) {
    string lowerContent = toLowerCase(content);
    size_t pos = lowerContent.find("i'm");

    if (pos == string::npos || (pos + 4) > content.size())
        return;
    string rem = content.substr(pos + 4);
    rem.erase(rem.size() - 2);
    string joke = "Hi <" + rem + ">, I'm Dad !";
    std::cout << joke << "\n";

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
               "for uuwu. \\(>w<)/";
    else
        joke = _jokes.at(roll(0, _jokes.size() - 1));
    string reply = "PRIVMSG " + target + " :" + joke + "\r\n";
    _socket.sendMessage(reply);
}

const char* Bot::InvalidNumberOfParametersException::what() const throw() {
    return "Error: Usage: ./ircbot <address> <password> [<port>]";
}

const char* Bot::InvalidPortException::what() const throw() {
    return "Error: Port has to be between 1 and 65535";
}