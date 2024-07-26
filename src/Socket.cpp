#include "Socket.hpp"

Socket::Socket() {}

Socket::~Socket() {}

int Socket::getFd() { return this->_fd; }