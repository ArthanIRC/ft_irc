#pragma once

#include <string>

#include "ClientSocket.hpp"

enum State { UNKNOWN, REGISTERED };

class Client {
  private:
    std::string _realname;
    std::string _nickname;
    std::string _username;
    std::string _modes;
    ClientSocket _socket;
    State _state;

  public:
    Client(int fd);
    ~Client();

    std::string const& getName() const;
    std::string const& getNickname() const;
    std::string const& getModes() const;
    ClientSocket& getSocket();
    bool isRegistered();
    State getState() const;
    void setState(State newState);
    void checkNameSyntaxCli(std::string nickname);
    void sendMessage(std::string message);
};