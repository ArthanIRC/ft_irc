#include <cstring>
#include <iostream>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "ClientSocket.hpp"
#include "Command.hpp"
#include "Exception.hpp"
#include "Replies.hpp"
#include "Server.hpp"

using std::map;
using std::string;

ClientSocket::ClientSocket(int fd, string ip) : Socket() {
    this->_fd = fd;
    this->_ip = ip;
}

ClientSocket::~ClientSocket() {}

void ClientSocket::onPoll(uint32_t events) {
    if ((events & EPOLLERR) || (events & EPOLLHUP) || (events & EPOLLRDHUP)) {
        removeSelf();
        return;
    }

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
        removeSelf();
        return;
    }

    Client* client;
    try {
        client = Server::getInstance().findClient(_fd);
    } catch (Server::ClientNotFoundException&) {
        return;
    }

    size_t i;
    do {
        i = data.find("\n");
        i = i == string::npos ? string::npos : i + 1;

        string line = data.substr(0, i);
        data = data.erase(0, i);

        if (!line.empty() && i == string::npos) {
            _rem = line;
            return;
        }

        if (!line.empty())
            executeCommand(line, client);
    } while (i != string::npos);
}

void ClientSocket::executeCommand(string data, Client* client) {
    Command* c;
    std::cerr << data;
    try {
        c = Command::create(data, client);
    } catch (RegFailedException&) {
        sendMessage(Replies::ERR_REGFAILED());
        removeSelf();
        return;
    } catch (ClientException& e) {
        string err = e.what();
        if (err != "std::exception")
            std::cout << e.what() << "\n";
        return;
    }

    try {
        c->run();
    } catch (ClientException& e) {
        std::cerr << e.what() << "\n";
    } catch (SendException& e) {
        std::cerr << e.what() << "\n";
        removeSelf();
    } catch (RegFailedException&) {
        sendMessage(Replies::ERR_REGFAILED());
        removeSelf();
        throw RegFailedException();
    }
    delete c;
}

void ClientSocket::sendMessage(string message) {
    if (send(_fd, message.c_str(), message.size(), MSG_NOSIGNAL) == -1)
        throw Socket::SendException();
}

void ClientSocket::removeSelf() {
    try {
        std::cout << "Client removed\n";
        Client* c = Server::getInstance().findClient(_fd);
        map<string, Channel*> channels = c->getChannels();
        string message = ":" + c->getSource() + " QUIT :Quit: Disconnected";
        Server::getInstance().sendMessage(channels, Message::create(message),
                                          c);
        Server::getInstance().removeClient(_fd);
    } catch (Server::ClientNotFoundException& e) {
        std::cerr << e.what() << "\n";
    }
}

string const& ClientSocket::getIp() const { return this->_ip; }