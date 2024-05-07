#include "Command.h"

// Extracts additional mode parameters from the command line input starting from the given index.
static std::string extractModeArguments(const std::vector<std::string> &parameters, size_t start)
{
	std::string mode_arguments;
	for (size_t i = start; i < parameters.size(); ++i)
	{
		if (!mode_arguments.empty())
			mode_arguments += " ";
		mode_arguments += parameters[i];
	}
	return mode_arguments;
}

// Returns a string representing the active modes of a channel.
static std::string getChannelModes(std::shared_ptr<Channel> channel_ptr)
{
	std::string modes = "+";
	if (channel_ptr->getModeI())
		modes += "i";
	if (channel_ptr->getModeL())
		modes += "l";
	if (channel_ptr->getModeT())
		modes += "t";
	if (channel_ptr->getModeK())
		modes += "k";
	return modes;
}

// Filters and validates the mode string from a command, ensuring only supported modes are processed.
void Command::extractMode(const Message &msg, const std::vector<std::string> &params, std::string &mode_string)
{
	std::string supported_modes = getChannelModes(server_->findChannel(params[0]));
	std::string validated_modes;
	mode_string = params[1];
	std::shared_ptr<Client> client_ptr = msg.getClientPtr();
	int fd = client_ptr->getFd();
	std::shared_ptr<Channel> channel_ptr = server_->findChannel(params[0]);

	for (char c : mode_string)
	{
		if (c == '+' || c == '-' || supported_modes.find(c) != std::string::npos)
			validated_modes += c;
		else
			server_->send_response(fd, ERR_UNKNOWNMODE(client_ptr->getNickname(), channel_ptr->getName(), c));
	}
	mode_string = validated_modes;
}

// Handles the MODE command, directing the processing and application of modes on channels.
void Command::handleMode(const Message &msg)
{
	std::shared_ptr<Client> client_ptr = msg.getClientPtr();
	int fd = client_ptr->getFd();
	std::vector<std::string> parameters = msg.getParameters();

	if (parameters.size() < 2)
	{
		server_->send_response(fd, ERR_NEEDMOREPARAMS(client_ptr->getClientPrefix(), "MODE"));
		return;
	}

	std::string target = parameters[0];
	std::string mode_string;
	std::string mode_arguments;

	std::shared_ptr<Channel> channel_ptr = server_->findChannel(target);
	if (!channel_ptr)
	{
		server_->send_response(fd, ERR_NOSUCHCHANNEL(server_->getServerHostname(), client_ptr->getNickname(), target));
		return;
	}

	if (parameters.size() > 2)
	{
		extractMode(msg, parameters, mode_string);
		mode_arguments = extractModeArguments(parameters, 2); // Extract mode arguments, like: MODE #channel +o user, where 'user' is the argument.
	}
	else
		mode_string = parameters[1];

	// Apply the extracted and validated modes
	applyChannelModes(channel_ptr, mode_string, mode_arguments, fd);
}

// Applies extracted and validated modes to the specified channel.
void Command::applyChannelModes(std::shared_ptr<Channel> channel, const std::string &mode_string, const std::string &mode_arguments, int fd)
{
	bool setting = true; // True when adding a mode, false when removing.
	size_t arg_index = 0;
	std::vector<std::string> args;
	std::istringstream arg_stream(mode_arguments);
	std::string arg;
	std::shared_ptr<Client> client_ptr = server_->findClientUsingFd(fd);
	// Split mode arguments into a vector
	while (arg_stream >> arg) // Extract arguments from the mode string
		args.push_back(arg);

	for (char mode : mode_string)
	{
		if (mode == '+')
		{
			setting = true;
			continue;
		}
		else if (mode == '-')
		{
			setting = false;
			continue;
		}

		switch (mode)
		{
		case 'i':
			channel->setModeI(setting);
			break;
		case 't': // Topic change restricted to channel operators
			channel->setModeT(setting);
			break;
		case 'l': // Limit the number of users in the channel
			if (setting)
			{
				if (arg_index < args.size()) // Check if a limit is provided
				{
					int limit = std::stoi(args[arg_index++]);
					channel->setModeL(true, limit);
				}
				else
					server_->send_response(fd, ERR_NEEDMOREPARAMS(client_ptr->getClientPrefix(), "MODE"));
			}
			else
				channel->setModeL(false);
			break;
		case 'k': // Set a password for the channel
			if (setting)
			{
				if (arg_index < args.size())
				{
					channel->setModeK(true);
					channel->setChannelKey(args[arg_index++]);
				}
				else
					// Send an error if no password is provided when setting 'k'
					server_->send_response(fd, ERR_NEEDMOREPARAMS(client_ptr->getClientPrefix(), "MODE"));
			}
			else
			{
				channel->setModeK(false);
				channel->setChannelKey("");
			}
			break;
		default:
			// If an unsupported mode is encountered, send an error message.
			server_->send_response(fd, ERR_UNKNOWNMODE(client_ptr->getNickname(), channel->getName(), mode));
			break;
		}
	}
}
