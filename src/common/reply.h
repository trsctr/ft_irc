#ifndef __REPLY_H__
#define __REPLY_H__

#define CRLF "\r\n"

// custom replies
#define PONG(servername, token) (":" + servername + " PONG " + servername + " :" + token + CRLF)
#define RPL_CHANGEMODE(client_prefix, channelname, mode, arguments) (":" + client_prefix + " MODE " + channelname + " " + mode + " " + arguments + CRLF)
#define RPL_INVITED(CLIENT, nickname, channelname) (":" + CLIENT + " INVITE " + nickname + " :" + channelname + CRLF)
#define RPL_JOINMSG(clientprefix, channelname) (":" + clientprefix + " JOIN " + channelname + CRLF)
#define RPL_KICK(clientprefix, channelname, nickname, msg) (":" + clientprefix + " KICK " + channelname + " " + nickname + " :" + msg + CRLF)
#define RPL_NICKCHANGECHANNEL(old_prefix, nickname) (":" + old_prefix + " NICK :" + nickname + CRLF)
#define RPL_NICKCHANGE(oldprefix, nickname) (":" + oldprefix + " NICK " + nickname + CRLF)

#define RPL_PRIVMSG(client_prefix, target, message) (":" + client_prefix + " PRIVMSG " + target + " :" + message + CRLF)
#define RPL_UMODECHANGE(NICK, mode) (":" + NICK + " MODE " + NICK + " :" + mode + CRLF)
#define RPL_QUIT(CLIENT, msg) (":" + CLIENT + " QUIT " + msg + CRLF)

// numerical replies

#define RPL_CONNECTED(servername, nickname, client_prefix) (":" + servername + " 001 " + nickname + " :Welcome to the best ever IRC server! " + client_prefix + CRLF)
#define RPL_ISUPPORT(servername, nickname) (":" + servername + " 005 " + nickname + " AWAYLEN=AWAY_MAX_LENGTH CHANMODES=l,k,it NICKLEN=NICK_MAX_LENGTH TOPICLEN=TOPIC_MAX_LENGTH MODES=4 KICKLEN=255 CHANTYPES=# CHANNELLEN=32 :are supported on this server" + CRLF)
#define RPL_UMODEIS(servername, nickname, modes) (":" + servername + " 221 " + nickname + " " + modes + CRLF)
#define RPL_AWAY(servername, nickname, recipient, message) (":" + servername + " 301 " + nickname + " " + recipient + " :" + message + CRLF)
#define RPL_UNAWAY(servername, nickname) (":" + servername + " 305 " + nickname + " :You are no longer marked as being away" + CRLF)
#define RPL_NOWAWAY(servername, nickname) (":" + servername + " 306 " + nickname + " :You have been marked as being away" + CRLF)
#define RPL_WHOISUSER(servername, user_nickname, whois_nickname, username, hostname, realname) (":" + servername + " 311 " + user_nickname + " " + whois_nickname + " ~" + username + " " + hostname + " * :" + realname + CRLF)
#define RPL_ENDOFWHO(servername, nickname, channelname) (":" + servername + " 315 " + nickname + " " + channelname + " " + ":End of /WHO list." + CRLF)
#define RPL_ENDOFWHOIS(servername, user_nickname, whois_nickname) (":" + servername + " 318 " + user_nickname + " " + whois_nickname + " :End of WHOIS list." + CRLF)
#define RPL_WHOISCHANNELS(nickname, channel) (": 319 " + nickname + " :" + channel + CRLF)
#define RPL_CHANNELMODEIS(servername, nickname, channelname, modes) (":" + servername + " 324 " + nickname + " " + channelname + " " + modes + CRLF)
#define RPL_CREATIONTIME(nickname, channelname, creationtime) (": 329 " + nickname + " " + channelname + " " + creationtime + CRLF)
#define RPL_NOTOPIC(servername, nickname, channelname) (":" + servername + " 331 " + nickname + " " + channelname + " :No topic is set" + CRLF)
#define RPL_TOPIC(servername, nickname, channelname, topic) (":" + servername + " 332 " + nickname + " " + channelname + " :" + topic + CRLF)
#define RPL_INVITING(servername, nickname, invited, channelname) (":" + servername + " 341 " + nickname + " " + invited + " " + channelname + CRLF)
#define RPL_WHOREPLY(servername, nick, channelname, username, host, userlist, flag, realname) (":" + servername + " 352 " + nick + " " + channelname + " ~" + username + " " + host + " " + userlist + " " + flag + "H" + " " + ":0 " + realname + CRLF)
#define RPL_NAMREPLY(servername, nickname, channelname, clientslist) (":" + servername + " 353 " + nickname + " = " + channelname + " :" + clientslist + CRLF)
#define RPL_ENDOFNAMES(servername, nickname, channelname) (":" + servername + " 366 " + nickname + " " + channelname + " :END of /NAMES list" + CRLF)
#define RPL_MOTD(servername, nickname, message)(":" + servername + " 372 " + nickname + " :- " + message + CRLF)
#define RPL_MOTDSTART(servername, nickname)(":" + servername + " 375 " + nickname + " :- " + servername + " Message of the day -" + CRLF)
#define RPL_MOTDEND(servername, nickname)(":" + servername + " 376 " + nickname + " :End of MOTD command" + CRLF)
#define ERR_NOSUCHNICK(servername, nickname, target) (":" + servername + " 401 " + nickname + " " + target +" :No such nick/channel" + CRLF)
#define ERR_NOSUCHCHANNEL(servername, nickname, channel_name) (":" + servername + " 403 " + nickname + " " + channel_name + " :No such channel" + CRLF)
#define ERR_CANNOTSENDTOCHAN(servername, nickname, channel) (":" + servername + " 404 " + nickname + " " + channel + " :Cannot send to channel" + CRLF)
#define ERR_NORECIPIENT(servername, nickname, command) (":" + servername + " 411 " + nickname + " " + command + " :No recipient given (" + command + ")" + CRLF)
#define ERR_NOTEXTTOSEND(servername, nickname) (":" + servername + " 412 " + nickname + " :No text to send" + CRLF)
#define ERR_CMDNOTFOUND(servername, nickname, command) (":" + servername + " 421 " + nickname + " " + command + " :Unknown command" + CRLF)
#define ERR_NONICKNAMEGIVEN(client_prefix) (client_prefix + " 431 :No nickname given" + CRLF)
#define ERR_ERRONEUSNICK(servername, nickname, bad_nickname) (":" + servername + " 432 " + nickname + " " + bad_nickname + " :Erroneus nickname" + CRLF)
#define ERR_NICKINUSE(servername, nickname) (":" + servername + " 433 * " + nickname + " :Nickname is already in use" + CRLF)
#define ERR_USERNOTINCHANNEL(servername, nickname, target_nick, channel) (":" + servername + " 441 " + nickname + " " + target_nick + " " + channel + " :They aren't on that channel" + CRLF)
#define ERR_USERONCHANNEL(servername, nickname, invited, channel) (":" + servername + " 443 " + nickname + " " + invited + " " + channel + " :is already on channel" + CRLF)
#define ERR_NOTONCHANNEL(servername, nickname, channelname) (":" + servername + " 442 " + nickname + " " + channelname + " :You're not on that channel" + CRLF)
#define ERR_NOTREGISTERED(servername) (":" + servername + " 451 " + "*" + " :You have not registered." + CRLF)
#define ERR_NEEDMOREPARAMS(client_prefix, command) (":" + client_prefix + " 461 " + command + " :Not enough parameters given." + CRLF)
#define ERR_ALREADYREGISTERED(servername, nickname) (":" + servername + " 462 " + nickname + " :You are already registered!" + CRLF)
#define ERR_INCORPASS(servername, nickname) (":" + servername + " 464 " + nickname + " :Password incorrect! try again!" + CRLF)
#define ERR_CHANNELISFULL(servername, nickname, channel) (":" + servername + " 471 " + nickname + " " + channel + " :Cannot join channel (+l)" + CRLF)
#define ERR_UNKNOWNMODE(servername, nickname, mode) (":" + servername + " 472 " + nickname + " " + mode + " :is unknown mode char to me" + CRLF)
#define ERR_INVITEONLYCHAN(servername, nickname, channel) (":" + servername + " 473 " + nickname + " " + channel + " :Cannot join channel (+i)" + CRLF)
#define ERR_BADCHANNELKEY(servername, nickname, channel) (":" + servername + " 475 " + nickname + " " + channel + " :Cannot join channel (+k)" + CRLF)
#define ERR_BADCHANMASK(servername, channel) (":" + servername + " 476 " + channel + " :Bad Channel Mask" + CRLF)
#define ERR_CHANOPRIVSNEEDED(servername, channel) (":" + servername + " 482 " + channel + " :You're not a channel operator" + CRLF)
#define ERR_NOOPERHOST(servername, nickname)(":" + servername + " 491 " + nickname + " No O-lines for your host" + CRLF)
#define ERR_UMODEUNKNOWNFLAG(servername, nickname, mode) (":" + servername + " 501 " + nickname + " " + mode + " :Unknown MODE flag" + CRLF)
#define ERR_USERSDONTMATCH(servername, nickname) (":" + servername + " 502 " + nickname + ":Can't change mode for other users" + CRLF)

#endif