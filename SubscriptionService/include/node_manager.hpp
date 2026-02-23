#ifndef SUBSCRIPTION_MANAGER_HPP
#define SUBSCRIPTION_MANAGER_HPP

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
#include "subscription_node.hpp"

class SUBSCRIPTIONSERVICE_API NodeManager {
public:
	NodeManager();
	~NodeManager();

	void addNode(const SubscriptionNode* node);
};

#endif // SUBSCRIPTION_MANAGER_HPP
