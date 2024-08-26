#pragma once

#include <string>

#include "ClientSocket.hpp"

enum State { UNKNOWN, PASS_DONE, NICK_DONE, USER_DONE, REGISTERED, OPERATOR };

class Client {
  private:
    std::string _realname;
    std::string _nickname;
    std::string _username;
    std::string _modes;
    ClientSocket _socket;
    State _state;
    bool _invisible;

  public:
    Client(int fd);
    ~Client();

    std::string const& getName() const;
    std::string const& getNickname() const;
    std::string getModes();
    ClientSocket& getSocket();
    bool isRegistered();
    bool isServerOperator();
    bool isInvisible();
    State getState() const;
    void setState(State newState);
    void setInvisible(bool state);
    void checkNameSyntaxCli(std::string nickname);
    void sendMessage(std::string message);
};