#pragma once

#include "Socket.hpp"

class ServerSocket : public Socket {
  private:
    struct addrinfo* _ai;
    bool _registered;

  public:
    ServerSocket();
    ~ServerSocket();

    void init(const char* port);
    void listen();
    void onPoll(uint32_t events);
    bool isRegistered();
    void setRegistered();
};