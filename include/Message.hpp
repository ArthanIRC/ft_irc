#pragma once

#include <string>
#include <vector>

class Message {
  private:
    static int parse(std::string& data, std::string& prefix,
                     std::string& command, std::vector<std::string>& params);
    static bool validate(const std::string& prefix, const std::string& command,
                         const std::vector<std::string>& params);

  protected:
    static const unsigned int max_params = 15;
    static const unsigned int err_trailing = 1001;
    static const unsigned int err_newline = 1002;
    static const unsigned int err_missing_cmd = 1003;

    std::string _prefix;
    std::string _command;
    std::vector<std::string> _params;

  public:
    virtual ~Message();

    std::string getRawMsg();

    static bool verify(std::string& data);

    virtual void run() = 0;

    class MissingCommandException : public std::exception {
      public:
        virtual const char* what() const throw() {
            return ("Missing command in message.");
        }
    };
    class WrongTrailingException : public std::exception {
      public:
        virtual const char* what() const throw() {
            return ("End of the message badly formatted.");
        }
    };
    class InvalidFormatException : public std::exception {
      public:
        virtual const char* what() const throw() {
            return ("Message format is invalid.");
        }
    };
    class NewlineException : public std::exception {
      public:
        virtual const char* what() const throw() {
            return ("Message contains a newline.");
        }
    };
    class UnknownErrorException : public std::exception {
      public:
        virtual const char* what() const throw() {
            return ("Unknown parsing error.");
        }
    };
};
