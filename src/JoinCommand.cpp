#include "JoinCommand.hpp"
#include <sstream>

JoinCommand::JoinCommand(std::string prefix, std::vector<std::string> params) {
    if (!prefix.empty()) {
        throw std::invalid_argument("JOIN command should not have a prefix.");
    }
    if (params.size() < 1 || params.size() > 2) {
        throw std::invalid_argument("JOIN command requires 1 or 2 parameters.");
    }

    std::string channels = params[0];
    std::string keys = params.size() == 2 ? params[1] : "";

    std::istringstream channelStream(channels);
    std::string channel;
    while (getline(channelStream, channel, ',')) {
        if (channel.empty() || (channel[0] != '#' && channel[0] != '&')) {
            throw std::invalid_argument("Invalid channel name: " + channel);
        }
    }

    if (!keys.empty()) {
        std::istringstream keyStream(keys);
        std::string key;
        while (getline(keyStream, key, ',')) {
            if (key.empty()) {
                throw std::invalid_argument("Invalid key: empty key provided.");
            }
        }
    }
}

void JoinCommand::run() { return; }