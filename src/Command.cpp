#include "Command.hpp"
#include "PassCommand.hpp"
#include <exception>
#include <iostream>
#include <string>

Command* Command::create(std::string& data) {
    try {
        Message::verify(data);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return (NULL);
    }
    std::string prefix, command;
    std::vector<std::string> params;
    data += "\r\n"; // ULTRA TMP MAIS POUR FAIRE MARCHER 2eme PARSING
    Message::parse(data, prefix, command, params);
    // int parse_result = Message::parse(data, prefix, command, params);
    // if (parse_result != 0) {
    //     std::cerr << "Parsing error: " << parse_result << std::endl;
    //     return NULL;
    // }
    try {
        //     if (command == "CAP") {
        //         return new CapCommand(prefix, params);
        //     }
        if (command == "PASS") {
            return new PassCommand(prefix, params);
        }
        // else if (command == "INVITE") {
        //     return new InviteCommand(prefix, params);
        // }
        // else if (command == "JOIN") {
        //     return new JoinCommand(prefix, params);
        // }
        // else if (command == "KICK") {
        //     return new KickCommand(prefix, params);
        // }
        // else if (command == "LUSERS") {
        //     return new LusersCommand(prefix, params);
        // }
        // else if (command == "MODE") {
        //     return new ModeCommand(prefix, params);
        // }
        // else if (command == "NICK") {
        //     return new NickCommand(prefix, params);
        // }
        // else if (command == "PRIVMESSAGE") {
        //     return new PrivMesageCommand(prefix, params);
        // }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return (NULL);
    }
    return (NULL);
}

// structure : GROS TRY avec if pour chaque commande, qui dedans va throw
// lerreur en question