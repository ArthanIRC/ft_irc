#pragma once

#include "Channel.hpp"
#include "Client.hpp"
#include "Message.hpp"
#include "Server.hpp"
#include <sstream>

class Replies : public Message {
  private:
    template <typename T> static std::string toString(T Number) {
        std::ostringstream ss;
        ss << Number;
        return ss.str();
    }

  public:
    virtual ~Replies(){};
    static std::string RPL_WELCOME(Client* client, Server& server);
    static std::string RPL_YOURHOST(Client* client, Server& server);
    static std::string RPL_CREATED(Client* client, Server& server);
    static std::string RPL_MYINFO(Client* client, Server& server);
    static std::string RPL_ISUPPORT1(Client* client, Server& server);
    static std::string RPL_ISUPPORT2(Client* client, Server& server);
    static std::string RPL_BOUNCE();
    static std::string RPL_STATSCOMMANDS();
    static std::string RPL_ENDOFSTATS();
    static std::string RPL_UMODEIS(Client* _client);
    static std::string RPL_STATSUPTIME();
    static std::string RPL_LUSERCLIENT(Client* client);
    static std::string RPL_LUSEROP(Client* client);
    static std::string RPL_LUSERUNKNOWN(Client* client);
    static std::string RPL_LUSERCHANNELS(Client* client);
    static std::string RPL_LUSERME(Client* client);
    static std::string RPL_ADMINME();
    static std::string RPL_ADMINLOC1();
    static std::string RPL_ADMINLOC2();
    static std::string RPL_ADMINEMAIL();
    static std::string RPL_TRYAGAIN();
    static std::string RPL_LOCALUSERS(Client* client);
    static std::string RPL_GLOBALUSERS(Client* client);
    static std::string RPL_WHOISCERTFP();
    static std::string RPL_NONE();
    static std::string RPL_AWAY();
    static std::string RPL_USERHOST();
    static std::string RPL_UNAWAY();
    static std::string RPL_NOWAWAY();
    static std::string RPL_WHOISREGNICK();
    static std::string RPL_WHOISUSER();
    static std::string RPL_WHOISSERVER();
    static std::string RPL_WHOISOPERATOR();
    static std::string RPL_WHOWASUSER();
    static std::string RPL_ENDOFWHO();
    static std::string RPL_WHOISIDLE();
    static std::string RPL_ENDOFWHOIS();
    static std::string RPL_WHOISCHANNELS();
    static std::string RPL_WHOISSPECIAL();
    static std::string RPL_LISTSTART();
    static std::string RPL_LIST();
    static std::string RPL_LISTEND();
    static std::string RPL_CHANNELMODEIS(Client* client, Channel* channel);
    static std::string RPL_CREATIONTIME();
    static std::string RPL_WHOISACCOUNT();
    static std::string RPL_NOTOPIC();
    static std::string RPL_TOPIC(Client* client, Channel* channel);
    static std::string RPL_TOPICWHOTIME();
    static std::string RPL_INVITELIST();
    static std::string RPL_ENDOFINVITELIST();
    static std::string RPL_WHOISACTUALLY();
    static std::string RPL_INVITING(Client* client, std::string targetName,
                                    Channel* channel);
    static std::string RPL_INVEXLIST();
    static std::string RPL_ENDOFINVEXLIST();
    static std::string RPL_EXCEPTLIST();
    static std::string RPL_ENDOFEXCEPTLIST();
    static std::string RPL_VERSION();
    static std::string RPL_WHOREPLY();
    static std::string RPL_NAMREPLY(Client* client, Channel* channel);
    static std::string RPL_LINKS();
    static std::string RPL_ENDOFLINKS();
    static std::string RPL_ENDOFNAMES(Client* client, std::string channelName);
    static std::string RPL_BANLIST(Client* client, Client* banned,
                                   Channel* chan);
    static std::string RPL_ENDOFBANLIST(Client* client, Channel* chan);
    static std::string RPL_ENDOFWHOWAS();
    static std::string RPL_INFO();
    static std::string RPL_MOTD(Client* client, std::string motd);
    static std::string RPL_ENDOFINFO();
    static std::string RPL_MOTDSTART(Client* client);
    static std::string RPL_ENDOFMOTD(Client* client);
    static std::string RPL_WHOISHOST();
    static std::string RPL_WHOISMODES();
    static std::string RPL_YOUREOPER();
    static std::string RPL_REHASHING();
    static std::string RPL_TIME();
    static std::string ERR_UNKNOWNERROR();
    static std::string ERR_NOSUCHNICK(Client* client, std::string& target);
    static std::string ERR_NOSUCHSERVER();
    static std::string ERR_NOSUCHCHANNEL(Client* client, std::string& chanName);
    static std::string ERR_CANNOTSENDTOCHAN(Client* client,
                                            std::string& chanName);
    static std::string ERR_TOOMANYCHANNELS();
    static std::string ERR_WASNOSUCHNICK();
    static std::string ERR_NOORIGIN();
    static std::string ERR_NORECIPIENT(Client* client);
    static std::string ERR_NOTEXTTOSEND(Client* client);
    static std::string ERR_INPUTTOOLONG();
    static std::string ERR_UNKNOWNCOMMAND();
    static std::string ERR_NOMOTD(Client* client);
    static std::string ERR_NONICKNAMEGIVEN(Client* client);
    static std::string ERR_ERRONEUSNICKNAME(Client* client, std::string& nick);
    static std::string ERR_NICKNAMEINUSE(Client* client, std::string& nick);
    static std::string ERR_NICKCOLLISION();
    static std::string ERR_USERNOTINCHANNEL(Client* client,
                                            std::string targetName,
                                            Channel* channel);
    static std::string ERR_NOTONCHANNEL(Client* client, Channel* channel);
    static std::string ERR_USERONCHANNEL(Client* client, std::string targetName,
                                         Channel* chan);
    static std::string ERR_NOTREGISTERED();
    static std::string ERR_NEEDMOREPARAMS(Client* client, std::string command);
    static std::string ERR_ALREADYREGISTERED(Client* client);
    static std::string ERR_PASSWDMISMATCH(Client* client);
    static std::string ERR_YOUREBANNEDCREEP();
    static std::string ERR_CHANNELISFULL(Client* client, Channel* channel);
    static std::string ERR_UNKNOWNMODE();
    static std::string ERR_INVITEONLYCHAN(Client* client, Channel* channel);
    static std::string ERR_BANNEDFROMCHAN(Client* client, Channel* channel);
    static std::string ERR_BADCHANNELKEY(Client* client, Channel* channel);
    static std::string ERR_BADCHANMASK();
    static std::string ERR_NOPRIVILEGES();
    static std::string ERR_CHANOPRIVSNEEDED(Client* client, Channel* channel);
    static std::string ERR_CANTKILLSERVER();
    static std::string ERR_NOOPERHOST();
    static std::string ERR_UMODEUNKNOWNFLAG(Client* client);
    static std::string ERR_USERSDONTMATCH(Client* client);
    static std::string ERR_HELPNOTFOUND();
    static std::string ERR_INVALIDKEY(Client* client, Channel* chan);
    static std::string RPL_STARTTLS();
    static std::string RPL_WHOISSECURE();
    static std::string ERR_STARTTLS();
    static std::string ERR_INVALIDMODEPARAM();
    static std::string RPL_HELPSTART();
    static std::string RPL_HELPTXT();
    static std::string RPL_ENDOFHELP();
    static std::string ERR_NOPRIVS();
    static std::string RPL_LOGGEDIN();
    static std::string RPL_LOGGEDOUT();
    static std::string ERR_NICKLOCKED();
    static std::string RPL_SASLSUCCESS();
    static std::string ERR_SASLFAIL();
    static std::string ERR_SASLTOOLONG();
    static std::string ERR_SASLABORTED();
    static std::string ERR_SASLALREADY();
    static std::string RPL_SASLMECHS();
    static std::string ERR_REGFAILED();
};
