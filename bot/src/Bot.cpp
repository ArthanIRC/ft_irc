#include <cstdlib>

#include "Bot.hpp"
#include "Server.hpp"

using std::string;

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

        // TODO: parse data, create response and do things
    }
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