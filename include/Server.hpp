#pragma once

#include <cstdlib>
#include <ctime>
#include <deque>
#include <exception>
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
    unsigned int _port;
    std::string _password;
    bool _signal;
    int _socketFd;
    struct sockaddr_in _socketAddr;
    std::vector<Client*> _clientServ;
    std::vector<Channel*> _channelServ;

    static const unsigned int defaultPort = 6667;

    void parsePort(const char* strp);
    void parsePassword(std::string pass);

  public:
    Server(int ac, char** data);
    ~Server();

    class InvalidNumberOfParametersException : public std::exception {
        virtual const char* what() const throw();
    };

    class InvalidPortException : public std::exception {
        virtual const char* what() const throw();
    };

    class EmptyPasswordException : public std::exception {
        virtual const char* what() const throw();
    };

    class NonAlnumPasswordException : public std::exception {
        virtual const char* what() const throw();
    };

    void signalHandler(int signal);
    void initSocket();
    int const& getSocketFd(void) const;
};
