#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Client {
  private:
    Client();
    std::string _realname;
    std::string _nickname;
    std::string _username;
    int _fd;

  public:
    Client(std::string name);
    ~Client();
    std::string const& getName() const;
    std::string const& getNickname() const;
    int const& getFd() const;
    void setFd(int& fd);
    void checkNameSyntaxCli(std::string nickname);
};