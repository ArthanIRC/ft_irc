#pragma once

#include "Exception.hpp"
#include <stdint.h>

class Socket {
  protected:
    const static int MAX_LIMIT = 4096;

    int _fd;

    Socket();
    virtual ~Socket();

  public:
    int getFd() const;
    virtual void onPoll(uint32_t events) = 0;

    class AcceptFailedException : public ClientException {
      public:
        virtual const char* what() const throw();
    };

    class AddrInfoException : public ServerException {
        virtual const char* what() const throw();
    };

    class BindFailedException : public ServerException {
        virtual const char* what() const throw();
    };

    class ClientNonBlockException : public ClientException {
      public:
        virtual const char* what() const throw();
    };

    class ConnectException : public ServerException {
      public:
        virtual const char* what() const throw();
    };

    class ListenFailedException : public ServerException {
        virtual const char* what() const throw();
    };

    class SendException : public ServerException {
      public:
        virtual const char* what() const throw();
    };

    class ServerNonBlockException : public ServerException {
        virtual const char* what() const throw();
    };

    class SocketCreationException : public ServerException {
        virtual const char* what() const throw();
    };
};