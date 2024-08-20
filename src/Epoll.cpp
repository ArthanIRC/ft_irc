#include "Epoll.hpp"
#include <sys/epoll.h>
#include <unistd.h>

Epoll::Epoll() {
    this->_epfd = epoll_create1(0);
    if (_epfd < 0)
        throw;
}

Epoll::~Epoll() {
    if (_epfd >= 0)
        close(_epfd);
}