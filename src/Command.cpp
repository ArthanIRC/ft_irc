#include "Command.hpp"
#include "InviteCommand.hpp"
#include "JoinCommand.hpp"
#include "PassCommand.hpp"

#include <exception>
#include <iostream>
#include <string>

Command* Command::create(std::string& data, Client* client) {
    try {
        Message::verify(data);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return (NULL);
    }
    std::string source, command;
    std::vector<std::string> params;
    data += "\r\n"; // ULTRA TMP MAIS POUR FAIRE MARCHER 2eme PARSING
    Message::parse(data, source, command, params);
    try {
        //     if (command == "CAP") {
        //         return new CapCommand(source, params);
        //     }
        if (command == "PASS") {
            return new PassCommand(source, params, client);
        } else if (command == "INVITE") {
            return new InviteCommand(source, params, client);
        } else if (command == "JOIN") {
            return new JoinCommand(source, params, client);
        }
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