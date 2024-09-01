#include "Command.hpp"
#include "CapCommand.hpp"
#include "InviteCommand.hpp"
#include "JoinCommand.hpp"
#include "KickCommand.hpp"
#include "LusersCommand.hpp"
#include "ModeCommand.hpp"
#include "MotdCommand.hpp"
#include "NamesCommand.hpp"
#include "NickCommand.hpp"
#include "OperCommand.hpp"
#include "PartCommand.hpp"
#include "PassCommand.hpp"
#include "PingCommand.hpp"
#include "PrivmsgCommand.hpp"
#include "TopicCommand.hpp"
#include "UserCommand.hpp"

#include <string>

Command* Command::create(std::string& data, Client* client) {
    Message::verify(data);
    std::string source, command;
    std::vector<std::string> params;
    data += "\r\n"; // ULTRA TMP MAIS POUR FAIRE MARCHER 2eme PARSING
    Message::parse(data, source, command, params);

    if (command == "CAP")
        return new CapCommand(source, params, client);
    else if (command == "INVITE")
        return new InviteCommand(source, params, client);
    else if (command == "JOIN")
        return new JoinCommand(source, params, client);
    else if (command == "KICK")
        return new KickCommand(source, params, client);
    else if (command == "LUSERS")
        return new LusersCommand(source, params, client);
    else if (command == "MODE")
        return new ModeCommand(source, params, client);
    else if (command == "MOTD")
        return new MotdCommand(source, params, client);
    else if (command == "NAMES")
        return new NamesCommand(source, params, client);
    else if (command == "NICK")
        return new NickCommand(source, params, client);
    else if (command == "OPER")
        return new OperCommand(source, params, client);
    else if (command == "PART")
        return new PartCommand(source, params, client);
    else if (command == "PASS")
        return new PassCommand(source, params, client);
    else if (command == "PING")
        return new PingCommand(source, params, client);
    else if (command == "PRIVMSG")
        return new PrivmsgCommand(source, params, client);
    else if (command == "TOPIC")
        return new TopicCommand(source, params, client);
    else if (command == "USER")
        return new UserCommand(source, params, client);
    else
        throw ClientException();
}