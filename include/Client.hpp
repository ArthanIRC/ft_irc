#pragma once

#include <string>

#include "ClientSocket.hpp"

enum State { UNKNOWN, REGISTERED };

class Client {
  private:
    std::string _realname;
    std::string _nickname;
    std::string _username;
    ClientSocket _socket;
    State _state;

  public:
    Client(int fd);
    ~Client();

    std::string const& getName() const;
    std::string const& getNickname() const;
    ClientSocket& getSocket();
    State getState() const;
    void setState(State newState);
    bool isRegistered();
    void checkNameSyntaxCli(std::string nickname);
};