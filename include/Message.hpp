#pragma once

#include <string>
#include <vector>

class Message {
	private:
		static const unsigned int ERR_NO_CMD = 1001;

		std::string               _rawMsg;
		std::string               _prefix;
		std::string               _command;
		std::vector<std::string>  _params;

		static int parse(std::string& data);
		static int validate(std::string& data);

	public:
		virtual ~Message();

		std::string getRawMsg();

		void setRaw(std::string& str);
		void setPrefix(std::string& str);
		void setCommand(std::string& str);
		void setParams(std::string& str);
		static void create(std::string& data);

		virtual void run() = 0;

		class MessageFormatException : public std::exception {
			public:
				virtual const char* what() const throw() {return ("Error: Message isn't properly formatted.");}
		};
};
