#pragma once

#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <netinet/in.h>
#include <set>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <vector>

#include "Channel.hpp"
#include "Client.hpp"
#include "Epoll.hpp"
#include "ServerSocket.hpp"

std::string toLowerCase(std::string s);

class Server {
  private:
    bool _running;
    std::string _port;
    std::string _password;
    size_t _maxClients;
    ServerSocket _socket;
    Epoll _epoll;
    std::vector<Client*> _clients;
    std::map<std::string, Channel*> _channels;
    std::map<std::string, std::string> _operators;

    Server();
    Server(Server const&);
    void operator=(Server const&);

  public:
    ~Server();

    static std::string parsePort(const char* strp);
    static std::string parsePassword(std::string pass);
    void init(int ac, char** data);
    void run();
    void stop();
    void addClient(Client* c);
    void addChannel(Channel* c);
    Client* findClient(int fd);
    Client* findClient(std::string nickname);
    Channel* findChannel(std::string name);
    std::string getSource();
    std::vector<Client*> getClients();
    std::map<std::string, Channel*> getChannels();
    std::map<std::string, std::string> getOperators();
    void removeClient(Client* c);
    void removeClient(int fd);
    bool isRunning() const;
    Epoll& getEpoll();
    std::string getPassword() const;
    std::string getMotd() const;
    std::string getNetworkName() const;
    std::string getServerName() const;
    std::string getVersion() const;
    std::string getCreationDate() const;
    std::string getUserModes() const;
    std::string getChannelModes() const;
    std::string getRplSupport1() const;
    std::string getRplSupport2() const;
    std::string getBotKey() const;
    size_t getMaxClients() const;
    std::set<Client*> getClientsSet(std::map<std::string, Channel*> channels,
                                    Client* sender);
    void sendMessage(Channel* channel, std::string message, Client* sender);
    void sendMessage(std::map<std::string, Channel*> channels,
                     std::string message, Client* sender);
    void sendMessageIfAway(Channel* channel, std::string message,
                           Client* sender);
    void sendMessageIfAway(std::map<std::string, Channel*> channels,
                           std::string message, Client* sender);
    void notifyPrivBot(std::string chanName);

    static Server& getInstance();

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

    class ClientNotFoundException : public std::exception {
      public:
        virtual const char* what() const throw();
    };

    class ChannelNotFoundException : public std::exception {
      public:
        virtual const char* what() const throw();
    };
};