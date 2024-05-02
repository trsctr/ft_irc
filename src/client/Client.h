#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "../headers.h"
#include "../server/Server.h"
#include "../command/Command.h"
#include "../message/Message.h"
#include "../channel/Channel.h"

class Server;
class Commands;
class Message;
class Channel;

class Client{
	private:
	int															fd_;
	bool														registered_;
	bool														password_; //true if server password is set
	std::string													nickname_;
	std::string													old_nickname_;
	std::string													username_;
	std::string													hostname_;
	std::string													realname_;
	char														usermode_;
	std::string													ip_address_;
	std::string													client_prefix_;
	std::string													buffer;
	bool														invited_;
	Channel*													channel;
	// TODO saving channels where the user is to the client class
	//  std::vector<std::shared_ptr<Channel>>	channels_;
	// TODO monitoring ping pong status
	// clients that have not replied in a long time should be dropped from the server

	public:
	Client() = default;
	Client(const int &fd, const std::string &nickname, const std::string &username, const std::string &ipaddress);
	~Client();

	// getters
	int			getFd();
	std::string getNickname();
	std::string getOldNickname();
	std::string getUsername();
	std::string getHostname();
	std::string getRealname();
	std::string getIpAddress();
	char		getUserMode();
	bool		getRegisterStatus();
	const std::string &getClientPrefix();

	// setters

	void		setFd(int const &fd);
	void		setNickname(std::string const &nickname);
	void		setUsername(std::string const &username);
	void		setHostname(std::string const &hostname);
	void		setRealname(std::string const &realname);
	void		setUserMode(char const &usermode);
	void		setIpAddress(std::string const &ip_address);
	void		setPassword();
	void        setClientPrefix();

	// member functions
	void		registerClient();
	void		unregisterClient();
	void 		processBuffer(Server *server_ptr);
	void 		appendToBuffer(const std::string& data);
	void		processCommand(Message &message, Server *server_ptr);
	bool		hasSentPassword();
	bool 		isInvited() const; // Check if the client is invited to a channel
	bool 		hasCorrectPassword(const std::string& password) const; // Check if the client has the correct password

	// void		sendMessage(std::string const &message);
	// std::string	receiveMessage();
	// void		joinChannel(std::string const &channel); this could maybe take a pointer instead of string?
};

#endif
