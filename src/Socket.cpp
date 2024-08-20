#include "Socket.hpp"
#include <unistd.h>

Socket::Socket() {}

Socket::~Socket() { close(this->_fd); }

int Socket::getFd() const { return this->_fd; }