#include "Replies.hpp"
#include "Channel.hpp"
#include "Message.hpp"

std::string Replies::RPL_WELCOME() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_YOURHOST() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_CREATED() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_MYINFO() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_ISUPPORT() {
    std::string reply;
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
    reply = "221 " + _client->getNickname() + _client->getModes();
    return Message::create(reply);
}

std::string Replies::RPL_STATSUPTIME() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_LUSERCLIENT() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_LUSEROP() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_LUSERUNKNOWN() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_LUSERCHANNELS() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_LUSERME() {
    std::string reply;
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

std::string Replies::RPL_LOCALUSERS() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_GLOBALUSERS() {
    std::string reply;
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

std::string Replies::RPL_CHANNELMODEIS() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_CREATIONTIME() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_WHOISACCOUNT() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_NOTOPIC() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_TOPIC(Client* client, Channel* channel) {
    std::string reply;
    reply = "332 " + client->getNickname() + " " + channel->getName() + " :" +
            channel->getTopic();
    return Message::create(reply);
}

std::string Replies::RPL_TOPICWHOTIME() {
    std::string reply;
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
    reply = "365 " + client->getNickname() + " " + channelName +
            " :End of /NAMES list";
    return Message::create(reply);
}

std::string Replies::RPL_BANLIST() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_ENDOFBANLIST() {
    std::string reply;
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

std::string Replies::RPL_MOTD() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_ENDOFINFO() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_MOTDSTART() {
    std::string reply;
    return Message::create(reply);
}

std::string Replies::RPL_ENDOFMOTD() {
    std::string reply;
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

std::string Replies::RPL_YOUREOPER() {
    std::string reply;
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
    reply = "411 " + client->getNickname() + " :No recipient given PRIVMSG";
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

std::string Replies::ERR_NOMOTD() {
    std::string reply;
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
    reply = "501 " + client->getNickname() + ":Unknown MODE flag";
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

std::string Replies::ERR_INVALIDKEY() {
    std::string reply;
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
