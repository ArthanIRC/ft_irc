#pragma once

#include <string>
#include <vector>

#define ERR_NO_CMD 1001

class Message {
  private:
    std::string               _rawMsg;
    std::string               _prefix;
    std::string               _command;
    std::vector<std::string>  _params;

    static int parse(std::string& data);
    static int validate(std::string& data);

  public:
    virtual ~Message();

    std::string getRawMsg();

    virtual void run() = 0;
};

static void create(std::string& data);