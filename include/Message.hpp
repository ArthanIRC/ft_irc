#pragma once

#include <string>

class Message {
  private:
    std::string _content;

    void validate(std::string& data);

  public:
    Message(std::string& data);
    virtual ~Message();

    virtual void run() = 0;
};