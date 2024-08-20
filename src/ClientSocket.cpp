#include "ClientSocket.hpp"

ClientSocket::ClientSocket(int fd) : Socket() { this->_fd = fd; }

ClientSocket::~ClientSocket() {}

void ClientSocket::onPoll() {
    // TODO: handle the event in the fd by receiving the data,
    // then creating the Message to be processed
}