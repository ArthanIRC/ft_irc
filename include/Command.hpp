#pragma once

#include "Message.hpp"

class Command : public Message {
  public:
    static Command* create(std::string& data);

    virtual void run() = 0; // a modifier avec un client un channel
};