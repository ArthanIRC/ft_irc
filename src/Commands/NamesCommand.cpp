#include "NamesCommand.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Replies.hpp"

NamesCommand::NamesCommand(std::string source, std::vector<std::string> aprams,
                           Client* client) {
    if (params.size() < 2) {
        // asd
    }
    this->_source = source;
}

NamesCommand::~NamesCommand(){};

void NamesCommand::run() {
    return;
    return;
}

/*
Channel map operator, la get et voir si client et dedans
Creer une map dans channel qui doit s’appeler voiceqqch
Get celle la aussi pour voir si voice
*/