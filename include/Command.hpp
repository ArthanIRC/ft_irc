#pragma once

#include "Client.hpp"
#include "Message.hpp"

class Command : public Message {
  protected:
    Client* _client;

  public:
    virtual ~Command(){};

    static Command* create(std::string& data, Client* client);

    virtual void run() = 0;
};
