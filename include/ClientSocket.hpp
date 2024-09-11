#pragma once

#include <string>

#include "Exception.hpp"
#include "Socket.hpp"

class Client;

class ClientSocket : public Socket {
  private:
    std::string _ip;
    std::string _rem;

    void removeSelf();
    void executeCommand(std::string data, Client* client);

    const static int MAX_LIMIT = 4096;

  public:
    ClientSocket(int fd, std::string ip);
    ~ClientSocket();

    void onPoll(uint32_t events);
    void sendMessage(std::string message);
    std::string const& getIp() const;

    class SendException : ServerException {
      public:
        virtual const char* what() const throw();
    };
};