#include <cstring>
#include <netdb.h>

#include "BotSocket.hpp"

using std::string;

BotSocket::BotSocket() : Socket(), _registered(false) {}

BotSocket::~BotSocket() { freeaddrinfo(_ai); }

void BotSocket::init(const char* ip, const char* port) {
    struct addrinfo hints, *ai;
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(ip, port, &hints, &ai)) != 0)
        throw Socket::AddrInfoException();

    this->_fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if (_fd < 0) {
        freeaddrinfo(ai);
        throw Socket::SocketCreationException();
    }

    this->_ai = ai;
}

void BotSocket::connect() {
    if (::connect(_fd, _ai->ai_addr, _ai->ai_addrlen) == -1)
        throw Socket::ConnectException();
}

void BotSocket::onPoll(uint32_t events) { (void)events; }

bool BotSocket::isEof() { return this->_eof; }

string BotSocket::receive() {
    char buf[MAX_LIMIT];
    string data;
    ssize_t size;
    memset(buf, 0, MAX_LIMIT);

    if (!_rem.empty()) {
        data.append(_rem);
        _rem.clear();
    }

    size = recv(_fd, buf, MAX_LIMIT, 0);
    data.append(buf);
    if (data.empty() || size == -1) {
        _eof = true;
        return "";
    }

    size_t i = data.find("\n");
    i = i == string::npos ? string::npos : i + 1;
    string line = data.substr(0, i);
    data = data.erase(0, i);
    if (!line.empty() && i == string::npos) {
        _rem = line;
        return "";
    }
    if (!data.empty())
        _rem = data;
    return line;
}

void BotSocket::sendMessage(string message) {
    if (send(_fd, message.c_str(), message.size(), MSG_NOSIGNAL) == -1)
        throw Socket::SendException();
}