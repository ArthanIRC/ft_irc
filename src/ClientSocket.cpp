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

ClientSocket::ClientSocket(int fd) : Socket() { this->_fd = fd; }

ClientSocket::~ClientSocket() {}

void ClientSocket::removeSelf() {
    try {
        Server::getInstance().removeClient(_fd);
    } catch (Server::ClientNotFoundException& e) {
        std::cerr << e.what() << "\n";
    }
}

void ClientSocket::onPoll(uint32_t events) {
    if ((events & EPOLLERR) || (events & EPOLLHUP) || (events & EPOLLRDHUP)) {
        removeSelf();
        return;
    }

    char buf[MAX_LIMIT];
    std::string data;
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

    Command* c = Command::create(data, client);

    try {
        c->run();
    } catch (ClientException&) {
        return;
    } catch (ServerException& e) {
        std::cerr << e.what() << "\n";
    }
}

void ClientSocket::sendMessage(std::string message) {
    if (send(_fd, message.c_str(), message.size(), 0) == -1)
        throw SendException();
}

const char* ClientSocket::SendException::what() const throw() {
    return "Error: Send failed.";
}