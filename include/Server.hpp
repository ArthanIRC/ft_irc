#pragma once

#include <cstdlib>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <netinet/in.h>
#include <stack>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <vector>

#include "Channel.hpp"
#include "Client.hpp"

class Server {
  private:
    Server();
    int _port;
    std::string _password;
    bool _signal;
    int _socketFd;
    struct sockaddr_in _socketAddr;
    std::vector<Client*> _clientServ;
    std::vector<Channel*> _channelServ;

  public:
    Server(int port, std::string password);
    ~Server();
    void signalHandler(int signal);
    void initSocket();
    int const& getSocketFd(void) const;
};
