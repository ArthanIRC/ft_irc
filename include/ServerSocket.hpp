#pragma once

#include "Socket.hpp"
#include <exception>

class ServerSocket : public Socket {
  private:
    struct addrinfo* _ai;

    void onPoll();

  public:
    ServerSocket(const char* port);
    ~ServerSocket();

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

    class AcceptFailedException : public std::exception {
        virtual const char* what() const throw();
    };

    class ClientNonBlockException : public std::exception {
        virtual const char* what() const throw();
    };

    void listen();
};