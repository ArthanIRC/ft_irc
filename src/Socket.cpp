#include "Socket.hpp"
#include <unistd.h>

Socket::Socket() {}

Socket::~Socket() {
    if (_fd >= 0)
        close(_fd);
}

int Socket::getFd() const { return this->_fd; }