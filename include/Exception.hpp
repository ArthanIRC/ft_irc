#pragma once

#include <exception>
#include <string>

class ClientException : public std::exception {};
class RegFailedException : public std::exception {
    std::string _msg;

  public:
    RegFailedException(const std::string& msg) {
        this->_msg = "Error: Registration failed\n" + msg;
    }
    RegFailedException() { this->_msg = "Error: registration failed."; }
    virtual ~RegFailedException() throw() {}

    virtual const char* what() const throw() { return _msg.c_str(); }
};
class ServerException : public std::exception {};