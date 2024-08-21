#pragma once

#include <stdint.h>

class Socket {
  protected:
    int _fd;

    Socket();
    virtual ~Socket();

  public:
    int getFd() const;
    virtual void onPoll(uint32_t events) = 0;
};