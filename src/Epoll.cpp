#include "Epoll.hpp"
#include <sys/epoll.h>

Epoll::Epoll() {
    int epfd = epoll_create(0);
    if (epfd < 0)
        throw;

    this->_epfd = epfd;
}