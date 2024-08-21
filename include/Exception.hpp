#pragma once

#include <exception>

class ClientException : public std::exception {};
class ServerException : public std::exception {};