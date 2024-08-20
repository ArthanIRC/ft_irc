#pragma once

class Epoll {
  public:
    Epoll();
    ~Epoll();

  private:
    int _epfd;

    void poll();
    void subscribe();
    void unsubscribe();
};