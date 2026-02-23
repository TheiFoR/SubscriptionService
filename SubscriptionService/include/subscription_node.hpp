#ifndef SUBSCRIPTION_NODE_HPP
#define SUBSCRIPTION_NODE_HPP

#ifdef _WIN32
#ifdef SUBSCRIPTIONSERVICE_EXPORTS
#define SUBSCRIPTIONSERVICE_API __declspec(dllexport)
#else
#define SUBSCRIPTIONSERVICE_API __declspec(dllimport)
#endif
#else
#define SUBSCRIPTIONSERVICE_API [[gnu::visibility("default")]]
#endif

#include <string>
#include <any>

#include "types/node_types.hpp"

class SUBSCRIPTIONSERVICE_API SubscriptionNode {
public:
	SubscriptionNode();
	virtual ~SubscriptionNode();
	
	void subscribe(const std::string& commandName, CommandFunction function);
	void unsubscribe(const std::string& commandName, CommandFunction function);

	void signalUCommand(const std::string& commandName, const std::any& data);
	void signalUPacket(const std::string& packetName, const std::any& data);
};

#endif // SUBSCRIPTION_NODE_HPP
