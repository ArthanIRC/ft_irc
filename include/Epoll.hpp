#pragma once

#include <exception>

#include "Socket.hpp"

class Epoll {
  private:
    int _epfd;
    static const int MAX_EVENTS = 32;
    static const int TIMEOUT = 3000;

  public:
    Epoll();
    ~Epoll();

    void subscribe(int fd, Socket& sock);
    void unsubscribe(int fd);
    void poll();

    class EpollSubscribeException : public std::exception {
        virtual const char* what() const throw();
    };

    class EpollUnsubscribeException : public std::exception {
        virtual const char* what() const throw();
    };

    class EpollWaitException : public std::exception {
        virtual const char* what() const throw();
    };
};