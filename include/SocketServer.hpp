#pragma once

#include "Socket.hpp"
#include <exception>

class SocketServer : public Socket {
  private:
    struct addrinfo* _ai;

  public:
    SocketServer(const char* port);
    ~SocketServer();

    class AddrInfoException : public std::exception {
        virtual const char* what() const throw();
    };

    class SocketCreationException : public std::exception {
        virtual const char* what() const throw();
    };

    class BindFailedException : public std::exception {
        virtual const char* what() const throw();
    };

    class ListenFailedException : public std::exception {
        virtual const char* what() const throw();
    };

    void listen();
};