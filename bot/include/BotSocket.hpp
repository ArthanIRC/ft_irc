#pragma once

#include <string>

#include "Socket.hpp"

class BotSocket : public Socket {
  private:
    struct addrinfo* _ai;
    bool _registered;
    bool _eof;
    std::string _rem;

  public:
    BotSocket();
    ~BotSocket();

    void init(const char* ip, const char* port);
    void connect();
    std::string receive();
    void sendMessage(std::string message);
    void onPoll(uint32_t events);
    void setRegistered();
    bool isRegistered();
    bool isEof();
};