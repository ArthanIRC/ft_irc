#pragma once

#include "Socket.hpp"

class ClientSocket : public Socket {
  private:
  public:
    ClientSocket(int fd);
    ~ClientSocket();

    void onPoll();
};