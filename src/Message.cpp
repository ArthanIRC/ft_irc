#include "Message.hpp"

Message::Message(std::string& data) { validate(data); }

Message::~Message() {}

void Message::validate(std::string& data) { this->_content = data; }