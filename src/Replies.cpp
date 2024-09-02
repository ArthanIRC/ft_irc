#include "Replies.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Message.hpp"
#include "Server.hpp"
#include <map>

std::string Replies::RPL_WELCOME(Client* client, Server& server) {
    std::string reply;
    reply = "001 " + client->getNickname() + " :Welcome to the " +
            server.getNetworkName() + " Network, " + client->getNickname();
    return Message::create(reply);
}

std::string Replies::RPL_YOURHOST(Client* client, Server& server) {
    std::string reply;
    reply = "002 " + client->getNickname() + " :Your host is " +
            server.getServerName() + ", running version " + server.getVersion();
    return Message::create(reply);
}

std::string Replies::RPL_CREATED(Client* client, Server& server) {
    std::string reply;
    reply = "003 " + client->getNickname() + " :This server was created " +
            server.getCreationDate();
    return Message::create(reply);
}

std::string Replies::RPL_MYINFO(Client* client, Server& server) {
    std::string reply;
    reply = "004 " + client->getNickname() + " " + server.getServerName() +
            " " + server.getVersion() + " " + server.getUserModes() + " " +
            server.getChannelModes();
    return Message::create(reply);
}

std::string Replies::RPL_ISUPPORT1(Client* client, Server& server) {
    std::string reply;
    reply = "005 " + client->getNickname() + " " + server.getRplSupport1() +
            " :are supported by this server";
    return Message::create(reply);
}

std::string Replies::RPL_ISUPPORT2(Client* client, Server& server) {
    std::string reply;
    reply = "005 " + client->getNickname() + " " + server.getRplSupport2() +
            " :are supported by this server";
    return Message::create(reply);
}

std::string Replies::RPL_BOUNCE() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_STATSCOMMANDS() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_ENDOFSTATS() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_UMODEIS(Client* _client) {
    std::string reply;
    reply = "221 " + _client->getNickname() + " " + _client->getModes();
    return Message::create(reply);
}

std::string Replies::RPL_STATSUPTIME() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_LUSERCLIENT(Client* client) {
    std::string reply;
    std::vector<Client*> clients = Server::getInstance().getClients();
    size_t u = clients.size();
    size_t i = 0;
    for (std::vector<Client*>::iterator it = clients.begin();
         it != clients.end(); it++) {
        if ((*it)->isInvisible())
            i++;
    }
    reply = "251 " + client->getNickname() + " :There are " + toString(u) +
            " users and " + toString(i) + " invisible on 1 servers";
    return Message::create(reply);
}

std::string Replies::RPL_LUSEROP(Client* client) {
    std::string reply;

    size_t ops = 0;
    std::vector<Client*> clients = Server::getInstance().getClients();
    for (std::vector<Client*>::iterator it = clients.begin();
         it != clients.end(); it++) {
        if ((*it)->getState() == OPERATOR)
            ops++;
    }

    reply = "252 " + client->getNickname() + " " + toString(ops) +
            " :operator(s) online";
    return Message::create(reply);
}

std::string Replies::RPL_LUSERUNKNOWN(Client* client) {
    std::string reply;
    size_t i = 0;
    std::vector<Client*> clients = Server::getInstance().getClients();
    for (std::vector<Client*>::iterator it = clients.begin();
         it != clients.end(); it++) {
        if ((*it)->getState() == UNKNOWN)
            i++;
    }
    reply = "253 " + client->getNickname() + " " + toString(i) +
            " :unknown connection(s)";
    return Message::create(reply);
}

std::string Replies::RPL_LUSERCHANNELS(Client* client) {
    std::string reply;
    size_t channels = Server::getInstance().getChannels().size();
    reply = "254 " + client->getNickname() + " " + toString(channels) +
            " :channels formed";
    return Message::create(reply);
}

std::string Replies::RPL_LUSERME(Client* client) {
    std::string reply;
    size_t c = Server::getInstance().getClients().size();
    reply = "255 " + client->getNickname() + " :I have " + toString(c) +
            " clients and 0 server(s)";
    return Message::create(reply);
}

std::string Replies::RPL_ADMINME() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_ADMINLOC1() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_ADMINLOC2() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_ADMINEMAIL() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_TRYAGAIN() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_LOCALUSERS(Client* client) {
    std::string reply;
    size_t u = Server::getInstance().getClients().size();
    size_t m = Server::getInstance().getMaxClients();
    reply = "265 " + client->getNickname() + " " + toString(u) + " " +
            toString(m) + " :Current local users " + toString(u) + ", max " +
            toString(m);
    return Message::create(reply);
}

std::string Replies::RPL_GLOBALUSERS(Client* client) {
    std::string reply;
    size_t u = Server::getInstance().getClients().size();
    size_t m = Server::getInstance().getMaxClients();
    reply = "266 " + client->getNickname() + " " + toString(u) + " " +
            toString(m) + " :Current global users " + toString(u) + ", max " +
            toString(m);
    return Message::create(reply);
}

std::string Replies::RPL_WHOISCERTFP() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_NONE() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_AWAY() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_USERHOST() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_UNAWAY() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_NOWAWAY() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_WHOISREGNICK() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_WHOISUSER() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_WHOISSERVER() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_WHOISOPERATOR() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_WHOWASUSER() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_ENDOFWHO() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_WHOISIDLE() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_ENDOFWHOIS() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_WHOISCHANNELS() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_WHOISSPECIAL() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_LISTSTART() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_LIST() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_LISTEND() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_CHANNELMODEIS(Client* client, Channel* channel) {
    std::string reply;
    reply = "324 " + client->getNickname() + " " + channel->getName() + " " +
            channel->getModes();
    return Message::create(reply);
}

std::string Replies::RPL_CREATIONTIME(Client* client, Channel* channel) {
    std::string reply;
    reply = "329 " + client->getNickname() + " " + channel->getName() + " " +
            toString(channel->getCreationTime());
    return Message::create(reply);
}

std::string Replies::RPL_WHOISACCOUNT() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_NOTOPIC(Client* client, Channel* channel) {
    std::string reply;
    reply = "331 " + client->getNickname() + " " + channel->getName() +
            " :No topic is set";
    return Message::create(reply);
}

std::string Replies::RPL_TOPIC(Client* client, Channel* channel) {
    std::string reply;
    reply = "332 " + client->getNickname() + " " + channel->getName() + " :" +
            channel->getTopic();
    return Message::create(reply);
}

std::string Replies::RPL_TOPICWHOTIME(Client* client, Channel* channel) {
    std::string reply;
    reply = "333 " + client->getNickname() + " " + channel->getName() + " " +
            channel->getLastTopicAuthor() + " " +
            toString(channel->getTopicSetTime());
    return Message::create(reply);
}

std::string Replies::RPL_INVITELIST() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_ENDOFINVITELIST() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_WHOISACTUALLY() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_INVITING(Client* client, std::string targetName,
                                  Channel* channel) {
    std::string reply;
    reply = "341 " + client->getNickname() + " INVITE " + targetName + " " +
            channel->getName();
    return Message::create(reply);
}

std::string Replies::RPL_INVEXLIST() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_ENDOFINVEXLIST() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_EXCEPTLIST() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_ENDOFEXCEPTLIST() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_VERSION() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_WHOREPLY() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_NAMREPLY(Client* client, Channel* channel) {
    std::string reply;
    reply = "353 " + client->getNickname() + " = " + channel->getName() + " :" +
            client->getNickname();
    std::map<std::string, Client*> mapClients = channel->getClients();
    std::map<std::string, Client*>::const_iterator it = mapClients.begin();
    std::string prefix;

    while (++it != mapClients.end()) {
        if (it->second->isInvisible() && !channel->isInChannel(client))
            continue;
        prefix = channel->getPrefix(it->second);
        reply += " " + prefix + it->first;
    }
    return Message::create(reply);
}

std::string Replies::RPL_LINKS() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_ENDOFLINKS() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_ENDOFNAMES(Client* client, std::string channelName) {
    std::string reply;
    reply = "366 " + client->getNickname() + " " + channelName +
            " :End of /NAMES list";
    return Message::create(reply);
}

std::string Replies::RPL_BANLIST(Client* client, Client* banned,
                                 Channel* chan) {
    std::string reply;
    reply = "367 " + client->getNickname() + " " + chan->getName() + " " +
            banned->getNickname();
    return Message::create(reply);
}

std::string Replies::RPL_ENDOFBANLIST(Client* client, Channel* chan) {
    std::string reply;
    reply = "368 " + client->getNickname() + " " + chan->getName() +
            " :End of channel ban list";
    return Message::create(reply);
}

std::string Replies::RPL_ENDOFWHOWAS() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_INFO() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_MOTD(Client* client, std::string motd) {
    std::string reply;
    reply = "372 " + client->getNickname() + " :" + motd;
    return Message::create(reply);
}

std::string Replies::RPL_ENDOFINFO() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_MOTDSTART(Client* client) {
    std::string reply;
    reply = "375 " + client->getNickname() + " :- Message of the day - ";
    return Message::create(reply);
}

std::string Replies::RPL_ENDOFMOTD(Client* client) {
    std::string reply;
    reply = "376 " + client->getNickname() + " :End of the /MOTD command.";
    return Message::create(reply);
}

std::string Replies::RPL_WHOISHOST() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_WHOISMODES() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_YOUREOPER(Client* client) {
    std::string reply;
    reply = "381 " + client->getNickname() + " :You are now an IRC operator";
    return Message::create(reply);
}

std::string Replies::RPL_REHASHING() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_TIME() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_UNKNOWNERROR() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_NOSUCHNICK(Client* client, std::string& target) {
    std::string reply;
    reply = "401 " + client->getNickname() + " " + target + " :No such nick";
    return Message::create(reply);
}

std::string Replies::ERR_NOSUCHSERVER() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_NOSUCHCHANNEL(Client* client, std::string& chanName) {
    std::string reply;
    reply =
        "403 " + client->getNickname() + " " + chanName + " :No such channel";
    return Message::create(reply);
}

std::string Replies::ERR_CANNOTSENDTOCHAN(Client* client,
                                          std::string& chanName) {
    std::string reply;
    reply = "404 " + client->getNickname() + " " + chanName +
            " :Cannot send to channel";
    return Message::create(reply);
}

std::string Replies::ERR_TOOMANYCHANNELS() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_WASNOSUCHNICK() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_NOORIGIN() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_NORECIPIENT(Client* client) {
    std::string reply;
    reply = "411 " + client->getNickname() + " :No recipient given (PRIVMSG)";
    return Message::create(reply);
}

std::string Replies::ERR_NOTEXTTOSEND(Client* client) {
    std::string reply;
    reply = "412 " + client->getNickname() + " :No text to send";
    return Message::create(reply);
}

std::string Replies::ERR_INPUTTOOLONG() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_UNKNOWNCOMMAND() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_NOMOTD(Client* client) {
    std::string reply;
    reply = "422 " + client->getNickname() + " :MOTD File is missing";
    return Message::create(reply);
}

std::string Replies::ERR_NONICKNAMEGIVEN(Client* client) {
    std::string reply;
    reply = "431 " + client->getNickname() + " :No nickname given";
    return Message::create(reply);
}

std::string Replies::ERR_ERRONEUSNICKNAME(Client* client, std::string& nick) {
    std::string reply;
    reply = "432 " + client->getNickname() + " " + nick + " :Erroneus nickname";
    return Message::create(reply);
}

std::string Replies::ERR_NICKNAMEINUSE(Client* client, std::string& nick) {
    std::string reply;
    reply = "433 " + client->getNickname() + " " + nick +
            " :Nickname is already in use";
    return Message::create(reply);
}

std::string Replies::ERR_NICKCOLLISION() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_USERNOTINCHANNEL(Client* client,
                                          std::string targetName,
                                          Channel* channel) {
    std::string reply;
    reply = "441 " + client->getNickname() + " " + targetName + " " +
            channel->getName() + " :They aren't on that channel";
    return Message::create(reply);
}

std::string Replies::ERR_NOTONCHANNEL(Client* client, Channel* channel) {
    std::string reply;
    reply = "442 " + client->getNickname() + " " + channel->getName() +
            " :You're not on that channel";
    return Message::create(reply);
}

std::string Replies::ERR_USERONCHANNEL(Client* client, std::string targetName,
                                       Channel* chan) {
    std::string reply;
    reply = "443 " + client->getNickname() + " " + targetName + " " +
            chan->getName() + " :is already on channel";
    return Message::create(reply);
}

std::string Replies::ERR_NOTREGISTERED() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_NEEDMOREPARAMS(Client* client, std::string command) {
    std::string reply;
    reply = "461 " + client->getNickname() + " " + command +
            " :Not enough parameters";
    return Message::create(reply);
}

std::string Replies::ERR_ALREADYREGISTERED(Client* client) {
    std::string reply;
    reply = "462 " + client->getNickname() + " :You may not reregister";
    return Message::create(reply);
}

std::string Replies::ERR_PASSWDMISMATCH(Client* client) {
    std::string reply;
    reply = "464 " + client->getNickname() + " :Password incorrect";
    return Message::create(reply);
}

std::string Replies::ERR_YOUREBANNEDCREEP() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_CHANNELISFULL(Client* client, Channel* channel) {
    std::string reply;
    reply = "471 " + client->getNickname() + " " + channel->getName() +
            " :Cannot join channel (+l)";
    return Message::create(reply);
}

std::string Replies::ERR_UNKNOWNMODE() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_INVITEONLYCHAN(Client* client, Channel* channel) {
    std::string reply;
    reply = "473 " + client->getNickname() + " " + channel->getName() +
            " :Cannot join channel (+i)";
    return Message::create(reply);
}

std::string Replies::ERR_BANNEDFROMCHAN(Client* client, Channel* channel) {
    std::string reply;
    reply = "474 " + client->getNickname() + " " + channel->getName() +
            " :Cannot join channel (+b)";
    return Message::create(reply);
}

std::string Replies::ERR_BADCHANNELKEY(Client* client, Channel* channel) {
    std::string reply;
    reply = "475 " + client->getNickname() + " " + channel->getName() +
            " :Cannot join channel (+k)";
    return Message::create(reply);
}

std::string Replies::ERR_BADCHANMASK() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_NOPRIVILEGES() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_CHANOPRIVSNEEDED(Client* client, Channel* channel) {
    std::string reply;
    reply = "482 " + client->getNickname() + " " + channel->getName() +
            " :You're not channel operator";
    return Message::create(reply);
}

std::string Replies::ERR_CANTKILLSERVER() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_NOOPERHOST() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_UMODEUNKNOWNFLAG(Client* client) {
    std::string reply;
    reply = "501 " + client->getNickname() + " :Unknown MODE flag";
    return Message::create(reply);
}

std::string Replies::ERR_USERSDONTMATCH(Client* client) {
    std::string reply;
    reply =
        "502 " + client->getNickname() + " :Cant change mode for other users";
    return Message::create(reply);
}

std::string Replies::ERR_HELPNOTFOUND() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_INVALIDKEY(Client* client, Channel* chan) {
    std::string reply;
    reply = "525 " + client->getNickname() + " " + chan->getName() +
            " :Key is not well-formed";
    return Message::create(reply);
}

std::string Replies::RPL_STARTTLS() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_WHOISSECURE() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_STARTTLS() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_INVALIDMODEPARAM() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_HELPSTART() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_HELPTXT() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_ENDOFHELP() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_NOPRIVS() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_LOGGEDIN() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_LOGGEDOUT() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_NICKLOCKED() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_SASLSUCCESS() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_SASLFAIL() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_SASLTOOLONG() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_SASLABORTED() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_SASLALREADY() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_SASLMECHS() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::ERR_REGFAILED() {
    std::string reply;
    reply = "ERROR :Registration failed";
    return Message::create(reply);
}
