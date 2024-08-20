#pragma once

#include <cstdlib>
#include <ctime>
#include <exception>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>

#include "Channel.hpp"
#include "Client.hpp"
#include "ServerSocket.hpp"

class Server {
  private:
    std::string _port;
    std::string _password;
    ServerSocket _socket;
    std::map<std::string, Client*> _clients;
    std::map<std::string, Channel*> _channels;

    static std::string parsePort(const char* strp);
    static std::string parsePassword(std::string pass);

  public:
    Server(std::string port, std::string password);
    ~Server();

    static Server create(int ac, char** data);

    void run();

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
};
