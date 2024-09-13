#pragma once

#include <exception>
#include <string>

#include "BotSocket.hpp"

class Bot {
  private:
    BotSocket _socket;
    std::string _password;
    bool _running;
    bool _registered;

    Bot();
    Bot(Bot const&);
    void operator=(Bot const&);

    void login();

  public:
    ~Bot();

    void init(int ac, char** data);
    void run();
    void stop();

    static Bot& getInstance();

    class InvalidNumberOfParametersException : public std::exception {
        virtual const char* what() const throw();
    };

    class InvalidPortException : public std::exception {
        virtual const char* what() const throw();
    };
};