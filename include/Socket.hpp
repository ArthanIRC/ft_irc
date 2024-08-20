#pragma once

class Socket {
  protected:
    int _fd;

    Socket();
    virtual ~Socket();

  public:
    int getFd() const;
    virtual void onPoll() = 0;
};