#include "Replies.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Message.hpp"
#include "Server.hpp"

using std::string;
using std::vector;

string Replies::RPL_WELCOME(Client* client, Server& server) {
    string reply;
    reply = "001 " + client->getNickname() + " :Welcome to the " +
            server.getNetworkName() + " Network, " + client->getNickname();
    return Message::create(reply);
}

string Replies::RPL_YOURHOST(Client* client, Server& server) {
    string reply;
    reply = "002 " + client->getNickname() + " :Your host is " +
            server.getServerName() + ", running version " + server.getVersion();
    return Message::create(reply);
}

string Replies::RPL_CREATED(Client* client, Server& server) {
    string reply;
    reply = "003 " + client->getNickname() + " :This server was created " +
            server.getCreationDate();
    return Message::create(reply);
}

string Replies::RPL_MYINFO(Client* client, Server& server) {
    string reply;
    reply = "004 " + client->getNickname() + " " + server.getServerName() +
            " " + server.getVersion() + " " + server.getUserModes() + " " +
            server.getChannelModes();
    return Message::create(reply);
}

string Replies::RPL_ISUPPORT1(Client* client, Server& server) {
    string reply;
    reply = "005 " + client->getNickname() + " " + server.getRplSupport1() +
            " :are supported by this server";
    return Message::create(reply);
}

string Replies::RPL_ISUPPORT2(Client* client, Server& server) {
    string reply;
    reply = "005 " + client->getNickname() + " " + server.getRplSupport2() +
            " :are supported by this server";
    return Message::create(reply);
}

string Replies::RPL_BOUNCE() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_STATSCOMMANDS() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_ENDOFSTATS() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_UMODEIS(Client* _client) {
    string reply;
    reply = "221 " + _client->getNickname() + " " + _client->getModes();
    return Message::create(reply);
}

string Replies::RPL_STATSUPTIME() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_LUSERCLIENT(Client* client) {
    string reply;
    vector<Client*> clients = Server::getInstance().getClients();
    size_t u = clients.size();
    size_t i = 0;
    for (vector<Client*>::iterator it = clients.begin(); it != clients.end();
         it++) {
        if ((*it)->isInvisible())
            i++;
    }
    reply = "251 " + client->getNickname() + " :There are " + toString(u) +
            " users and " + toString(i) + " invisible on 1 servers";
    return Message::create(reply);
}

string Replies::RPL_LUSEROP(Client* client) {
    string reply;

    size_t ops = 0;
    vector<Client*> clients = Server::getInstance().getClients();
    for (vector<Client*>::iterator it = clients.begin(); it != clients.end();
         it++) {
        if ((*it)->getState() == OPERATOR)
            ops++;
    }

    reply = "252 " + client->getNickname() + " " + toString(ops) +
            " :operator(s) online";
    return Message::create(reply);
}

string Replies::RPL_LUSERUNKNOWN(Client* client) {
    string reply;
    size_t i = 0;
    vector<Client*> clients = Server::getInstance().getClients();
    for (vector<Client*>::iterator it = clients.begin(); it != clients.end();
         it++) {
        if ((*it)->getState() == UNKNOWN)
            i++;
    }
    reply = "253 " + client->getNickname() + " " + toString(i) +
            " :unknown connection(s)";
    return Message::create(reply);
}

string Replies::RPL_LUSERCHANNELS(Client* client) {
    string reply;
    size_t channels = Server::getInstance().getChannels().size();
    reply = "254 " + client->getNickname() + " " + toString(channels) +
            " :channels formed";
    return Message::create(reply);
}

string Replies::RPL_LUSERME(Client* client) {
    string reply;
    size_t c = Server::getInstance().getClients().size();
    reply = "255 " + client->getNickname() + " :I have " + toString(c) +
            " clients and 0 server(s)";
    return Message::create(reply);
}

string Replies::RPL_ADMINME() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_ADMINLOC1() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_ADMINLOC2() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_ADMINEMAIL() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_TRYAGAIN() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_LOCALUSERS(Client* client) {
    string reply;
    size_t u = Server::getInstance().getClients().size();
    size_t m = Server::getInstance().getMaxClients();
    reply = "265 " + client->getNickname() + " " + toString(u) + " " +
            toString(m) + " :Current local users " + toString(u) + ", max " +
            toString(m);
    return Message::create(reply);
}

string Replies::RPL_GLOBALUSERS(Client* client) {
    string reply;
    size_t u = Server::getInstance().getClients().size();
    size_t m = Server::getInstance().getMaxClients();
    reply = "266 " + client->getNickname() + " " + toString(u) + " " +
            toString(m) + " :Current global users " + toString(u) + ", max " +
            toString(m);
    return Message::create(reply);
}

string Replies::RPL_WHOISCERTFP() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_NONE() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_AWAY(Client* sender, Client* recipient) {
    string reply;
    reply = "301 " + sender->getNickname() + " " + recipient->getNickname() +
            " :" + recipient->getAwayMsg();
    return Message::create(reply);
}

string Replies::RPL_USERHOST() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_UNAWAY(Client* client) {
    string reply;
    reply = "305 " + client->getNickname() +
            " :You are no longer marked as being away";
    return Message::create(reply);
}

string Replies::RPL_NOWAWAY(Client* client) {
    string reply;
    reply =
        "306 " + client->getNickname() + " :You have been marked as being away";
    return Message::create(reply);
}

string Replies::RPL_WHOISREGNICK() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_WHOISUSER() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_WHOISSERVER() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_WHOISOPERATOR() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_WHOWASUSER() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_ENDOFWHO(Client* client, string& mask) {
    string reply;
    reply = "315 " + client->getNickname() + " " + mask + " :End of WHO list";
    return Message::create(reply);
}

string Replies::RPL_WHOISIDLE() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_ENDOFWHOIS() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_WHOISCHANNELS() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_WHOISSPECIAL() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_LISTSTART() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_LIST() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_LISTEND() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_CHANNELMODEIS(Client* client, Channel* channel) {
    string reply;
    reply = "324 " + client->getNickname() + " " + channel->getName() + " " +
            channel->getModes();
    return Message::create(reply);
}

string Replies::RPL_CREATIONTIME(Client* client, Channel* channel) {
    string reply;
    reply = "329 " + client->getNickname() + " " + channel->getName() + " " +
            toString(channel->getCreationTime());
    return Message::create(reply);
}

string Replies::RPL_WHOISACCOUNT() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_NOTOPIC(Client* client, Channel* channel) {
    string reply;
    reply = "331 " + client->getNickname() + " " + channel->getName() +
            " :No topic is set";
    return Message::create(reply);
}

string Replies::RPL_TOPIC(Client* client, Channel* channel) {
    string reply;
    reply = "332 " + client->getNickname() + " " + channel->getName() + " :" +
            channel->getTopic();
    return Message::create(reply);
}

string Replies::RPL_TOPICWHOTIME(Client* client, Channel* channel) {
    string reply;
    reply = "333 " + client->getNickname() + " " + channel->getName() + " " +
            channel->getLastTopicAuthor() + " " +
            toString(channel->getTopicSetTime());
    return Message::create(reply);
}

string Replies::RPL_INVITELIST() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_ENDOFINVITELIST() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_WHOISACTUALLY() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_INVITING(Client* client, string targetName,
                             Channel* channel) {
    string reply;
    reply = "341 " + client->getNickname() + " INVITE " + targetName + " " +
            channel->getName();
    return Message::create(reply);
}

string Replies::RPL_INVEXLIST() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_ENDOFINVEXLIST() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_EXCEPTLIST() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_ENDOFEXCEPTLIST() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_VERSION() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_WHOREPLY(Client* client, Client* target, Channel* channel) {
    string reply;
    string flags = " ";
    string chanName = "*";

    if (target->isAway())
        flags += "G";
    else
        flags += "H";
    if (target->isServerOperator())
        flags += "*";
    if (channel) {
        flags += channel->getPrefix(target);
        chanName = channel->getName();
    }

    reply = "352 " + client->getNickname() + " " + chanName + " " +
            target->getUserName() + " localhost " +
            Server::getInstance().getSource() + " " + target->getNickname() +
            flags + " :0 " + target->getRealName();
    return Message::create(reply);
}

string Replies::RPL_NAMREPLY(Client* client, Channel* channel) {
    string reply;
    reply = "353 " + client->getNickname() + " = " + channel->getName() + " :" +
            channel->getPrefix(client) + client->getNickname();
    vector<Client*> clients = channel->getClients();
    vector<Client*>::const_iterator it = clients.begin();
    string prefix;

    while (++it != clients.end()) {
        if ((*it)->isInvisible() && !channel->isInChannel(client))
            continue;
        prefix = channel->getPrefix(*it);
        reply += " " + prefix + (*it)->getNickname();
    }
    return Message::create(reply);
}

string Replies::RPL_LINKS() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_ENDOFLINKS() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_ENDOFNAMES(Client* client, string channelName) {
    string reply;
    reply = "366 " + client->getNickname() + " " + channelName +
            " :End of /NAMES list";
    return Message::create(reply);
}

string Replies::RPL_BANLIST(Client* client, Client* banned, Channel* chan) {
    string reply;
    reply = "367 " + client->getNickname() + " " + chan->getName() + " " +
            banned->getNickname();
    return Message::create(reply);
}

string Replies::RPL_ENDOFBANLIST(Client* client, Channel* chan) {
    string reply;
    reply = "368 " + client->getNickname() + " " + chan->getName() +
            " :End of channel ban list";
    return Message::create(reply);
}

string Replies::RPL_ENDOFWHOWAS() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_INFO() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_MOTD(Client* client, string motd) {
    string reply;
    reply = "372 " + client->getNickname() + " :" + motd;
    return Message::create(reply);
}

string Replies::RPL_ENDOFINFO() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_MOTDSTART(Client* client) {
    string reply;
    reply = "375 " + client->getNickname() + " :- Message of the day - ";
    return Message::create(reply);
}

string Replies::RPL_ENDOFMOTD(Client* client) {
    string reply;
    reply = "376 " + client->getNickname() + " :End of the /MOTD command.";
    return Message::create(reply);
}

string Replies::RPL_WHOISHOST() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_WHOISMODES() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_YOUREOPER(Client* client) {
    string reply;
    reply = "381 " + client->getNickname() + " :You are now an IRC operator";
    return Message::create(reply);
}

string Replies::RPL_REHASHING() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_TIME() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_UNKNOWNERROR() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_NOSUCHNICK(Client* client, string& target) {
    string reply;
    reply = "401 " + client->getNickname() + " " + target + " :No such nick";
    return Message::create(reply);
}

string Replies::ERR_NOSUCHSERVER() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_NOSUCHCHANNEL(Client* client, string& chanName) {
    string reply;
    reply =
        "403 " + client->getNickname() + " " + chanName + " :No such channel";
    return Message::create(reply);
}

string Replies::ERR_CANNOTSENDTOCHAN(Client* client, string& chanName) {
    string reply;
    reply = "404 " + client->getNickname() + " " + chanName +
            " :Cannot send to channel";
    return Message::create(reply);
}

string Replies::ERR_TOOMANYCHANNELS() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_WASNOSUCHNICK() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_NOORIGIN() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_NORECIPIENT(Client* client) {
    string reply;
    reply = "411 " + client->getNickname() + " :No recipient given (PRIVMSG)";
    return Message::create(reply);
}

string Replies::ERR_NOTEXTTOSEND(Client* client) {
    string reply;
    reply = "412 " + client->getNickname() + " :No text to send";
    return Message::create(reply);
}

string Replies::ERR_INPUTTOOLONG() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_UNKNOWNCOMMAND() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_NOMOTD(Client* client) {
    string reply;
    reply = "422 " + client->getNickname() + " :MOTD File is missing";
    return Message::create(reply);
}

string Replies::ERR_NONICKNAMEGIVEN(Client* client) {
    string reply;
    reply = "431 " + client->getNickname() + " :No nickname given";
    return Message::create(reply);
}

string Replies::ERR_ERRONEUSNICKNAME(Client* client, string& nick) {
    string reply;
    reply = "432 " + client->getNickname() + " " + nick + " :Erroneus nickname";
    return Message::create(reply);
}

string Replies::ERR_NICKNAMEINUSE(Client* client, string& nick) {
    string reply;
    reply = "433 " + client->getNickname() + " " + nick +
            " :Nickname is already in use";
    return Message::create(reply);
}

string Replies::ERR_NICKCOLLISION() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_USERNOTINCHANNEL(Client* client, string targetName,
                                     Channel* channel) {
    string reply;
    reply = "441 " + client->getNickname() + " " + targetName + " " +
            channel->getName() + " :They aren't on that channel";
    return Message::create(reply);
}

string Replies::ERR_NOTONCHANNEL(Client* client, Channel* channel) {
    string reply;
    reply = "442 " + client->getNickname() + " " + channel->getName() +
            " :You're not on that channel";
    return Message::create(reply);
}

string Replies::ERR_USERONCHANNEL(Client* client, string targetName,
                                  Channel* chan) {
    string reply;
    reply = "443 " + client->getNickname() + " " + targetName + " " +
            chan->getName() + " :is already on channel";
    return Message::create(reply);
}

string Replies::ERR_NOTREGISTERED() {
    string reply;
    reply = "451 * :You have not registered";
    return Message::create(reply);
}

string Replies::ERR_NEEDMOREPARAMS(Client* client, string command) {
    string reply;
    reply = "461 " + client->getNickname() + " " + command +
            " :Not enough parameters";
    return Message::create(reply);
}

string Replies::ERR_ALREADYREGISTERED(Client* client) {
    string reply;
    reply = "462 " + client->getNickname() + " :You may not reregister";
    return Message::create(reply);
}

string Replies::ERR_PASSWDMISMATCH(Client* client) {
    string reply;
    reply = "464 " + client->getNickname() + " :Password incorrect";
    return Message::create(reply);
}

string Replies::ERR_YOUREBANNEDCREEP() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_CHANNELISFULL(Client* client, Channel* channel) {
    string reply;
    reply = "471 " + client->getNickname() + " " + channel->getName() +
            " :Cannot join channel (+l)";
    return Message::create(reply);
}

string Replies::ERR_UNKNOWNMODE() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_INVITEONLYCHAN(Client* client, Channel* channel) {
    string reply;
    reply = "473 " + client->getNickname() + " " + channel->getName() +
            " :Cannot join channel (+i)";
    return Message::create(reply);
}

string Replies::ERR_BANNEDFROMCHAN(Client* client, Channel* channel) {
    string reply;
    reply = "474 " + client->getNickname() + " " + channel->getName() +
            " :Cannot join channel (+b)";
    return Message::create(reply);
}

string Replies::ERR_BADCHANNELKEY(Client* client, Channel* channel) {
    string reply;
    reply = "475 " + client->getNickname() + " " + channel->getName() +
            " :Cannot join channel (+k)";
    return Message::create(reply);
}

string Replies::ERR_BADCHANMASK() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_NOPRIVILEGES() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_CHANOPRIVSNEEDED(Client* client, Channel* channel) {
    string reply;
    reply = "482 " + client->getNickname() + " " + channel->getName() +
            " :You're not channel operator";
    return Message::create(reply);
}

string Replies::ERR_CANTKILLSERVER() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_NOOPERHOST() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_UMODEUNKNOWNFLAG(Client* client) {
    string reply;
    reply = "501 " + client->getNickname() + " :Unknown MODE flag";
    return Message::create(reply);
}

string Replies::ERR_USERSDONTMATCH(Client* client) {
    string reply;
    reply =
        "502 " + client->getNickname() + " :Cant change mode for other users";
    return Message::create(reply);
}

string Replies::ERR_HELPNOTFOUND() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_INVALIDKEY(Client* client, Channel* chan) {
    string reply;
    reply = "525 " + client->getNickname() + " " + chan->getName() +
            " :Key is not well-formed";
    return Message::create(reply);
}

string Replies::RPL_STARTTLS() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_WHOISSECURE() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_STARTTLS() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_INVALIDMODEPARAM() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_HELPSTART() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_HELPTXT() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_ENDOFHELP() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_NOPRIVS() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_LOGGEDIN() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_LOGGEDOUT() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_NICKLOCKED() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_SASLSUCCESS() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_SASLFAIL() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_SASLTOOLONG() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_SASLABORTED() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_SASLALREADY() {
    string reply;
    return Message::create(reply);
}

string Replies::RPL_SASLMECHS() {
    string reply;
    return Message::create(reply);
}

string Replies::ERR_REGFAILED() {
    string reply;
    reply = "ERROR :Registration failed";
    return Message::create(reply);
}

std::string Replies::ERR_QUIT() {
    std::string reply;
    reply = "ERROR :No hard feelings, goodbye.";
    return Message::create(reply);
}