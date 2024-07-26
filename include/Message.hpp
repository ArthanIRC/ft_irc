#pragma once

#include <string>
#include <vector>

class Message {
	protected:
		static const unsigned int	err_no_cmd = 1001;
		static const unsigned int	err_syntax = 1002;
		static const unsigned int	max_params = 15;

		std::string					_prefix;
		std::string					_command;
		std::vector<std::string> 	_params;

		static int parse(std::string& data,std::string& prefix, std::string& command, std::vector<std::string>& params);
		static int validate(const std::string& prefix, const std::string& command, const std::vector<std::string>& params);

	public:
		virtual ~Message();

		std::string getRawMsg();

		static void create(std::string& data);

		virtual void run() = 0;

		class MissingCommandException : public std::exception {
			public:
				virtual const char* what() const throw() {return ("Error: Missing command in message.");}
		};
		class InvalidFormatException : public std::exception {
			public:
				virtual const char* what() const throw() {return ("Error: Message format is invalid.");}
		};
};
