#pragma once

#include "Socket.hpp"

class ClientSocket : public Socket {
  private:
    void removeSelf();

    const static int MAX_LIMIT = 4096;

  public:
    ClientSocket(int fd);
    ~ClientSocket();

    void onPoll(uint32_t events);
};