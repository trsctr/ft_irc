#ifndef CHANNEL_H
#define CHANNEL_H

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <memory>
#include <cctype>
#include "../client/Client.h"
#include "../common/MagicNumbers.h"
#include "../server/Server.h"

class Client;
class Server;
class Channel
{
	private:
		std::string 							name_; // Channel name
		std::map<std::shared_ptr<Client>, bool> users_; // Users in the channel and their operator status (true if op)
		std::string 							channel_key_; // Channel key
		std::pair<std::string, std::string> 	topic_; // Channel topic (author, topic)
		bool 									mode_t_; // Topic lock mode
		bool									mode_i_; // Invite-only mode
		bool									mode_k_; // Key-protected mode
		bool 									mode_l_; // User limit mode
		std::string 							mode_; // Channel modes
		unsigned int 							limit_;
		std::shared_ptr<Server>					server_;

	public:
		Channel(const std::string &name);
		~Channel();

		// Accessor methods
		std::string getName() const;
		std::map<std::shared_ptr<Client>, bool> getUsers() const;
		std::string getChannelKey() const;
		std::pair<std::string, std::string> getTopic() const;
		bool getModeT() const;
		bool getModeI() const;
		bool getModeK() const;
		bool getModeL() const;
		std::string const &getMode() const;

		// Mutator methods
		void setName(const std::string &name);
		void setUsers(const std::map<std::shared_ptr<Client>, bool> &users);
		void setUserCount(unsigned int usercount);
		void setChannelKey(const std::string &channel_key);
		void setTopic(const std::pair<std::string, std::string> &topic);
		void setModeT(bool mode_t);
		void setModeI(bool mode_i);
		void setModeK(bool mode_k);
		void setModeL(bool mode_l, unsigned int limit = DEFAULT_MAX_CLIENTS);
		void setMode(const std::string &mode);

		// Functional methods
		bool isFull() const;
		bool isInviteOnly() const;
		bool isPasswordProtected() const;
		void addUser(std::shared_ptr<Client> client, bool isOp);
		void removeUser(std::shared_ptr<Client> client);
		bool isUserOnChannel(std::string const &nickname);
		bool userIsOperator(std::string const &nickname);
		void updateTopic(const std::string& newTopic, const std::string& author, bool isAdmin);
		bool isValidChannelName(const std::string& channelName) const;
		void broadcastMessage(const std::string &senderNickname, const std::string &message);
		bool isOperator(std::shared_ptr<Client> client_ptr);
		bool canChangeTopic(std::shared_ptr<Client> client_ptr);
};

#endif // CHANNEL_H
