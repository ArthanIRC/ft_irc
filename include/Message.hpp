#pragma once

#include <string>
#include <vector>

class Message {
  protected:
    static const unsigned int max_params = 15;

    std::string _prefix;
    std::string _command;
    std::vector<std::string> _params;

    static bool parse(std::string& data, std::string& prefix,
                      std::string& command, std::vector<std::string>& params);
    static bool validate(const std::string& prefix, const std::string& command,
                         const std::vector<std::string>& params);

  public:
    virtual ~Message();

    std::string getRawMsg();

    static void create(std::string& data);

    virtual void run() = 0;

    class MissingCommandException : public std::exception {
      public:
        virtual const char* what() const throw() {
            return ("Error: Missing command in message.");
        }
    };
    class InvalidFormatException : public std::exception {
      public:
        virtual const char* what() const throw() {
            return ("Error: Message format is invalid.");
        }
    };
};
