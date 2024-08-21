#pragma once

#include <exception>

#include "Exception.hpp"
#include "Socket.hpp"

class ServerSocket : public Socket {
  private:
    struct addrinfo* _ai;
    bool _registered;

  public:
    ServerSocket();
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

    class ServerNonBlockException : public std::exception {
        virtual const char* what() const throw();
    };

    class AcceptFailedException : public ClientException {
      public:
        virtual const char* what() const throw();
    };

    class ClientNonBlockException : public ClientException {
      public:
        virtual const char* what() const throw();
    };

    void init(const char* port);
    void listen();
    void onPoll(uint32_t events);
    bool isRegistered();
    void setRegistered();
};