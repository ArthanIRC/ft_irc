#pragma once

#include <string>
#include <vector>

class Message {
  protected:
    static const unsigned int max_params = 15;
    static const unsigned int err_trailing = 1001;
    static const unsigned int err_newline = 1002;
    static const unsigned int err_missing_cmd = 1003;

    std::string _prefix;
    std::string _command;
    std::vector<std::string> _params;

    static int parse(std::string& data, std::string& prefix,
                     std::string& command, std::vector<std::string>& params);
    static bool validate(const std::string& prefix, const std::string& command,
                         const std::vector<std::string>& params);

  public:
    virtual ~Message();

    std::string getRawMsg();

    static bool verify(std::string& data);

    virtual void run() = 0;

    class MissingCommandException : public std::exception {
      public:
        virtual const char* what() const throw() {
            return ("Error: Missing command in message.");
        }
    };
    class WrongTrailingException : public std::exception {
      public:
        virtual const char* what() const throw() {
            return ("Error: End of the message badly formatted.");
        }
    };
    class InvalidFormatException : public std::exception {
      public:
        virtual const char* what() const throw() {
            return ("Error: Message format is invalid.");
        }
    };
    class NewlineException : public std::exception {
      public:
        virtual const char* what() const throw() {
            return ("Error: Message contains a newline.");
        }
    };
    class UnknownErrorException : public std::exception {
      public:
        virtual const char* what() const throw() {
            return ("Error: Unknown parsing error.");
        }
    };
};
