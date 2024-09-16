#pragma once

#include "Exception.hpp"
#include <string>
#include <vector>

class Message {
  private:
    static bool validate(const std::string& source, const std::string& command,
                         const std::vector<std::string>& params);

  protected:
    static int parse(std::string& data, std::string& source,
                     std::string& command, std::vector<std::string>& params,
                     bool addTrailing);

    static const unsigned int max_params = 15;
    static const unsigned int err_trailing = 1001;
    static const unsigned int err_newline = 1002;
    static const unsigned int err_missing_cmd = 1003;

    std::string _source;
    std::string _command;
    std::vector<std::string> _params;

  public:
    virtual ~Message();

    std::string getRawMsg();

    static bool verify(std::string& data);
    static std::string create(std::string& data);
    static std::vector<std::string> split(std::string& str, char delim);

    virtual void run() = 0;

    class MissingCommandException : public ClientException {
      public:
        virtual const char* what() const throw() {
            return ("Error: Missing command in message.");
        }
    };
    class WrongTrailingException : public ClientException {
      public:
        virtual const char* what() const throw() {
            return ("Error: End of the message badly formatted.");
        }
    };
    class InvalidFormatException : public ClientException {
      public:
        virtual const char* what() const throw() {
            return ("Error: Message format is invalid.");
        }
    };
    class NewlineException : public ClientException {
      public:
        virtual const char* what() const throw() {
            return ("Error: Message contains a newline.");
        }
    };
    class UnknownErrorException : public ClientException {
      public:
        virtual const char* what() const throw() {
            return ("Error: Unknown parsing error.");
        }
    };
};
