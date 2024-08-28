#pragma once

#include <string>

#include "Exception.hpp"
#include "Socket.hpp"

class ClientSocket : public Socket {
  private:
    void removeSelf();

    const static int MAX_LIMIT = 4096;

  public:
    ClientSocket(int fd);
    ~ClientSocket();

    void onPoll(uint32_t events);
    void sendMessage(std::string message);

    class SendException : ServerException {
      public:
        virtual const char* what() const throw();
    };
};