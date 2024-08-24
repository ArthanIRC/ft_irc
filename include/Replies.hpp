#pragma once

#include "Channel.hpp"
#include "Client.hpp"
#include "Message.hpp"

class Replies : public Message {
  public:
    virtual ~Replies(){};
    static std::string RPL_WELCOME();
    static std::string RPL_YOURHOST();
    static std::string RPL_CREATED();
    static std::string RPL_MYINFO();
    static std::string RPL_ISUPPORT();
    static std::string RPL_BOUNCE();
    static std::string RPL_STATSCOMMANDS();
    static std::string RPL_ENDOFSTATS();
    static std::string RPL_UMODEIS();
    static std::string RPL_STATSUPTIME();
    static std::string RPL_LUSERCLIENT();
    static std::string RPL_LUSEROP();
    static std::string RPL_LUSERUNKNOWN();
    static std::string RPL_LUSERCHANNELS();
    static std::string RPL_LUSERME();
    static std::string RPL_ADMINME();
    static std::string RPL_ADMINLOC1();
    static std::string RPL_ADMINLOC2();
    static std::string RPL_ADMINEMAIL();
    static std::string RPL_TRYAGAIN();
    static std::string RPL_LOCALUSERS();
    static std::string RPL_GLOBALUSERS();
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
    static std::string RPL_CHANNELMODEIS();
    static std::string RPL_CREATIONTIME();
    static std::string RPL_WHOISACCOUNT();
    static std::string RPL_NOTOPIC();
    static std::string RPL_TOPIC(const std::string& nickname,
                                 const std::string& chanName,
                                 const std::string& topic);
    static std::string RPL_TOPICWHOTIME();
    static std::string RPL_INVITELIST();
    static std::string RPL_ENDOFINVITELIST();
    static std::string RPL_WHOISACTUALLY();
    static std::string RPL_INVITING();
    static std::string RPL_INVEXLIST();
    static std::string RPL_ENDOFINVEXLIST();
    static std::string RPL_EXCEPTLIST();
    static std::string RPL_ENDOFEXCEPTLIST();
    static std::string RPL_VERSION();
    static std::string RPL_WHOREPLY();
    static std::string RPL_NAMREPLY();
    static std::string RPL_LINKS();
    static std::string RPL_ENDOFLINKS();
    static std::string RPL_ENDOFNAMES();
    static std::string RPL_BANLIST();
    static std::string RPL_ENDOFBANLIST();
    static std::string RPL_ENDOFWHOWAS();
    static std::string RPL_INFO();
    static std::string RPL_MOTD();
    static std::string RPL_ENDOFINFO();
    static std::string RPL_MOTDSTART();
    static std::string RPL_ENDOFMOTD();
    static std::string RPL_WHOISHOST();
    static std::string RPL_WHOISMODES();
    static std::string RPL_YOUREOPER();
    static std::string RPL_REHASHING();
    static std::string RPL_TIME();
    static std::string ERR_UNKNOWNERROR();
    static std::string ERR_NOSUCHNICK();
    static std::string ERR_NOSUCHSERVER();
    static std::string ERR_NOSUCHCHANNEL(const std::string& nickname,
                                         const std::string& chanName);
    static std::string ERR_CANNOTSENDTOCHAN();
    static std::string ERR_TOOMANYCHANNELS();
    static std::string ERR_WASNOSUCHNICK();
    static std::string ERR_NOORIGIN();
    static std::string ERR_NORECIPIENT();
    static std::string ERR_NOTEXTTOSEND();
    static std::string ERR_INPUTTOOLONG();
    static std::string ERR_UNKNOWNCOMMAND();
    static std::string ERR_NOMOTD();
    static std::string ERR_NONICKNAMEGIVEN();
    static std::string ERR_ERRONEUSNICKNAME();
    static std::string ERR_NICKNAMEINUSE();
    static std::string ERR_NICKCOLLISION();
    static std::string ERR_USERNOTINCHANNEL();
    static std::string ERR_NOTONCHANNEL(const std::string& nickname,
                                        const std::string& chanName);
    static std::string ERR_USERONCHANNEL();
    static std::string ERR_NOTREGISTERED();
    static std::string ERR_NEEDMOREPARAMS(const std::string& nickname,
                                          std::string command);
    static std::string ERR_ALREADYREGISTERED();
    static std::string ERR_PASSWDMISMATCH();
    static std::string ERR_YOUREBANNEDCREEP();
    static std::string ERR_CHANNELISFULL();
    static std::string ERR_UNKNOWNMODE();
    static std::string ERR_INVITEONLYCHAN();
    static std::string ERR_BANNEDFROMCHAN();
    static std::string ERR_BADCHANNELKEY();
    static std::string ERR_BADCHANMASK();
    static std::string ERR_NOPRIVILEGES();
    static std::string ERR_CHANOPRIVSNEEDED(const std::string& nickname,
                                            const std::string& chanName);
    static std::string ERR_CANTKILLSERVER();
    static std::string ERR_NOOPERHOST();
    static std::string ERR_UMODEUNKNOWNFLAG();
    static std::string ERR_USERSDONTMATCH();
    static std::string ERR_HELPNOTFOUND();
    static std::string ERR_INVALIDKEY();
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
};
