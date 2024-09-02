#pragma once

#include <map>
#include <string>

#include "ClientSocket.hpp"

class Channel;

enum State {
    UNKNOWN,
    CAP_STARTED,
    PASS_DONE,
    NICK_DONE,
    USER_DONE,
    REGISTERED,
    OPERATOR
};

class Client {
  private:
    std::string _realname;
    std::string _nickname;
    std::string _username;
    std::string _modes;
    ClientSocket _socket;
    State _state;
    bool _capEndedEarly;
    bool _invisible;
    bool _away;

  public:
    Client(int fd);
    ~Client();

    std::string const& getName() const;
    std::string const& getNickname() const;
    std::string const getSource() const;
    std::string getModes();
    ClientSocket& getSocket();
    std::map<std::string, Channel*> getChannels();
    bool isRegistered();
    bool isServerOperator();
    bool isAway();
    bool isInvisible();
    bool hasCapEndedEarly();
    State getState() const;
    void setState(State newState);
    void setInvisible(bool state);
    void setAway(bool state);
    void setCapEndedEarly();
    void setNickname(std::string& nick);
    void setUsername(std::string& username);
    void setRealname(std::string& realname);
    void sendMessage(std::string message);
};