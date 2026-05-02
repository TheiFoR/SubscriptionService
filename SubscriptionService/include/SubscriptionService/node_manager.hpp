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

#include <cstddef>
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <shared_mutex>
#include <vector>

#include <asio/io_context.hpp>

#include "SubscriptionService/subscription_node.hpp"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

class SUBSCRIPTIONSERVICE_API NodeManager{
public:
	NodeManager();
	~NodeManager();

	void addNode(const SubscriptionNode* node);
	void removeNode(const SubscriptionNode* node);

private:
	class Impl;
    std::unique_ptr<Impl> m_impl;

	std::thread m_implThread;
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // SUBSCRIPTION_MANAGER_HPP
