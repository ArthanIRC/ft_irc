#include "Message.hpp"
#include <cstdio>
#include <string>

Message::~Message() {}

void	Message::create(std::string& data) {
	std::string					prefix;
	std::string					command;
	std::vector<std::string>	params;

	if (Message::parse(data, prefix, command, params) == err_no_cmd) {
		throw (Message::MissingCommandException());
	}
	if (Message::validate()) {
		throw (Message::InvalidFormatException());
	}
}

int Message::parse(std::string& data, std::string& prefix, std::string& command, std::vector<std::string>& params) {
	std::istringstream			iss(data);
	std::string					word;

	if (data[0] == ':') {
		iss >> word;
		prefix = word.substr(1);
	}

	if (!(iss >> command)) {
		return (err_no_cmd);
	}

	while (iss >> word) {
		if (word[0] == ':') {
			std::string	trailing;
			getline(iss, trailing);
			word.erase(0,1);
			word += trailing;
			params.push_back(trailing);
			break ;
		}
		params.push_back(word);
	}
	return (0);
}

int	Message::validate()