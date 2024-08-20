#pragma once

class Socket {
  protected:
    int _fd;

    Socket();
    virtual ~Socket();

    virtual void onPoll() = 0;

  public:
    int getFd() const;
};