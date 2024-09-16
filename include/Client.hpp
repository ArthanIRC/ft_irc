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
    std::string _awayMsg;
    ClientSocket _socket;
    State _state;
    bool _capEndedEarly;
    bool _invisible;
    bool _away;
    bool _awayNotify;
    bool _bot;

  public:
    Client(int fd, std::string ip);
    ~Client();

    std::string const& getNickname() const;
    std::string const& getUserName() const;
    std::string const& getRealName() const;
    std::string const& getIp() const;
    std::string const getSource() const;
    std::string getModes();
    std::string const& getAwayMsg() const;
    ClientSocket& getSocket();
    std::map<std::string, Channel*> getChannels();
    State getState() const;

    void setState(State newState);
    void setInvisible(bool state);
    void setAway(bool state, std::string message);
    void setAwayNotify(bool state);
    void setBot(bool state);
    void setCapEndedEarly();
    void setNickname(std::string& nick);
    void setUsername(std::string& username);
    void setRealname(std::string& realname);

    bool isRegistered();
    bool isServerOperator();
    bool isAway();
    bool isAwayNotify();
    bool isInvisible();
    bool isBot();
    bool hasCapEndedEarly();

    void sendMessage(std::string message);
};