#include "KickCommand.hpp"

KickCommand::KickCommand(std::string prefix, std::vector<std::string> params) {
    if (params.size() < 2) {
        throw std::invalid_argument(
            "KICK command requires at least two parameters: <channel> <user>.");
    }

    // At this point, you would typically process the command, e.g.:
    std::string channel = params[0];
    std::string user = params[1];
    std::string comment = params.size() > 2 ? params[2] : "";

    // Debug output to verify that the command was parsed correctly
    std::cout << "KICK command received: Channel = " << channel
              << ", User = " << user;
    if (!comment.empty()) {
        std::cout << ", Comment = " << comment;
    }
    std::cout << std::endl;

    // You can add more logic here, like actually processing the kick
}