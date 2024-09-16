#pragma once

#include <exception>
#include <string>
#include <vector>

#include "BotSocket.hpp"

class Bot {
  private:
    BotSocket _socket;
    std::string _password;
    std::string _nickname;
    std::vector<std::string> _jokes;
    bool _running;
    bool _registered;

    Bot();
    Bot(Bot const&);
    void operator=(Bot const&);

    std::string joinPara(std::vector<std::string>& splitData, size_t i);
    std::vector<std::string> parse(std::string& data);

    void checkSender();
    void readFile();
    int roll(int min, int max);
    void login();
    void execute(std::vector<std::string> message);
    void imDad(std::string source, std::string target, std::string content);
    void joke(std::string source, std::string target);

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