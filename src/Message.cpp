#include "Message.hpp"
#include <cstdio>
#include <string>

Message::~Message() {}

void	Message::create(std::string& data) {
	std::string					prefix, command;
	std::vector<std::string>	params;

	if (Message::parse(data, prefix, command, params) == err_no_cmd) {
		throw (Message::MissingCommandException());
	}
	if (Message::validate(prefix, command, params) == err_syntax) {
		throw (Message::InvalidFormatException());
	}

	// ici message valide donc appel de commande etc
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

int Message::validate(const std::string& prefix, const std::string& command, const std::vector<std::string>& params) {
	if (!prefix.empty()) {
		for (size_t i = 0; i < prefix.length(); ++i) {
			if (!std::isalnum(prefix[i]) && prefix[i] != '-' && prefix[i] != '.') {
				return (err_syntax);
			}
		}
	}

	if (command.empty()) {
		return (err_syntax);
	}
	if (command.length() > 10) {
		return (err_syntax);
	}
	for (std::string::const_iterator it = command.begin(); it != command.end(); ++it) {
		if (!std::isupper(*it) && !std::isdigit(*it)) {
			return (err_syntax);
		}
	}

	if (params.size() > max_params) {
		return (err_syntax);
	}

	for (size_t i = 0; i < params.size(); ++i) {
		if (params[i].empty()) {
			return (err_syntax);
		}
		for (size_t j = 0; j < params[i].length(); ++j) {
			if (!std::isprint(params[i][j])) {
				return (err_syntax);
			}
		}
	}

	return (0);
}