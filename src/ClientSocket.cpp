#include <cstring>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "ClientSocket.hpp"
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

    // TODO: Command creation
}