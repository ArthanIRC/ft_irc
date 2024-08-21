#include "KickCommand.hpp"

// KickCommand::KickCommand(std::string prefix, std::vector<std::string> params)
// {
// PREFIX pas obligatoire mais a check
//     if (params.size() < 2) {
//         throw std::invalid_argument(
//             "KICK command requires at least two parameters: <channel>
//             <user>.");
//     }
//     std::string channel = params[0];
//     std::string user = params[1];
//     std::string comment = params.size() > 2 ? params[2] : "";

//     std::cout << "KICK command received: Channel = " << channel
//               << ", User = " << user;
//     if (!comment.empty()) {
//         std::cout << ", Comment = " << comment;
//     }
//     std::cout << std::endl;
// }