#include <cstring>
#include <sys/epoll.h>
#include <unistd.h>

#include "Epoll.hpp"
#include "Server.hpp"
#include "Socket.hpp"

Epoll::Epoll() {
    this->_epfd = epoll_create1(0);
    if (_epfd < 0)
        throw;
}

Epoll::~Epoll() {
    if (_epfd >= 0)
        close(_epfd);
}

void Epoll::subscribe(int fd, Socket& sock) {
    struct epoll_event event;
    memset(&event, 0, sizeof(struct epoll_event));

    event.events = EPOLLIN | EPOLLRDHUP;
    event.data.ptr = &sock;

    if (epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &event) < 0)
        throw Epoll::EpollSubscribeException();
}

void Epoll::unsubscribe(int fd) {
    if (epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, NULL) < 0)
        throw Epoll::EpollUnsubscribeException();
}

void Epoll::poll() {
    struct epoll_event events[MAX_EVENTS];
    int fds = epoll_wait(_epfd, events, MAX_EVENTS, TIMEOUT);

    if (fds == -1) {
        if (!Server::getInstance().isRunning())
            return;
        throw Epoll::EpollWaitException();
    }

    for (int i = 0; i < fds; i++) {
        ((Socket*)events[i].data.ptr)->onPoll(events[i].events);
    }
}

const char* Epoll::EpollSubscribeException::what() const throw() {
    return "Error: Creation of subscriber failed";
}

const char* Epoll::EpollUnsubscribeException::what() const throw() {
    return "Error: Deletion of subscriber failed";
}

const char* Epoll::EpollWaitException::what() const throw() {
    return "Error: Epoll wait failed";
}