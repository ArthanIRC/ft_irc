#pragma once

class Socket {
  protected:
    int _fd;

  public:
    Socket();
    virtual ~Socket() = 0;

    int getFd();
};