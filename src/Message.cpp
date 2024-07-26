#include "Message.hpp"
#include <cstdio>
#include <string>

Message::~Message() {}

void	Message::setRaw(std::string& str) {
	this->_rawMsg = str;
}

void	Message::setPrefix(std::string& str) {
	this->_prefix = str;
}

void	Message::setCommand(std::string& str) {
	this->_command = str;
}

void	Message::setParams(std::string& str) {
	this->_params.push_back(str);
}

void	Message::create(std::string& data) {
	if ((Message::parse(data) != 0) || (Message::validate(data) != 0)) {
		throw (Message::MessageFormatException());
	}
}

int Message::parse(std::string& data) {
	std::istringstream	iss(data);
	std::string			word;

	if (data[0] == ':') {
		iss >> word;
		this->_prefix = word.substr(1);
	}

	if (!(iss >> this->_command)) {
		return (ERR_NO_CMD);
	}

	while (iss >> word) {
		if (word[0] == ':') {
			std::string	trailing;
			getline(iss, trailing);
			word.erase(0,1);
			word += trailing;
			this->_params.push_back(trailing);
			break ;
		}
		this->_params.push_back(word);
	}
}