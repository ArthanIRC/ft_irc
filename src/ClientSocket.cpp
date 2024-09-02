#include <cstring>
#include <iostream>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "ClientSocket.hpp"
#include "Command.hpp"
#include "Exception.hpp"
#include "Server.hpp"

using std::string;

ClientSocket::ClientSocket(int fd) : Socket() { this->_fd = fd; }

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

    while ((size = recv(_fd, buf, MAX_LIMIT, 0)) != 0) {
        if (size == -1)
            break;
        data.append(buf);
        memset(buf, 0, MAX_LIMIT);
    }

    if (data.empty()) {
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

        if (!line.empty())
            executeCommand(line, client);
    } while (i != string::npos);
}

void ClientSocket::executeCommand(string data, Client* client) {
    Command* c;
    std::cout << data;
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
    }
}

void ClientSocket::sendMessage(string message) {
    if (send(_fd, message.c_str(), message.size(), 0) == -1)
        throw SendException();
}

void ClientSocket::removeSelf() {
    try {
        std::cout << "Client removed\n";
        Server::getInstance().removeClient(_fd);
    } catch (Server::ClientNotFoundException& e) {
        std::cerr << e.what() << "\n";
    }
}

const char* ClientSocket::SendException::what() const throw() {
    return "Error: Send failed.";
}