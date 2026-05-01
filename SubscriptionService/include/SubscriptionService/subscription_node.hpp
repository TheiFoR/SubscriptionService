#ifndef SUBSCRIPTIONSERVICE_SUBSCRIPTION_NODE_HPP
#define SUBSCRIPTIONSERVICE_SUBSCRIPTION_NODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#ifdef _WIN32
#ifdef SUBSCRIPTIONSERVICE_EXPORTS
#define SUBSCRIPTIONSERVICE_API __declspec(dllexport)
#else
#define SUBSCRIPTIONSERVICE_API __declspec(dllimport)
#endif
#else
#define SUBSCRIPTIONSERVICE_API [[gnu::visibility("default")]]
#endif

#include <any>
#include <memory>
#include <string>
#include <thread>

#include <asio/io_context.hpp>

#include "SubscriptionService/types/node_types.hpp"

class NodeManager;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

class SUBSCRIPTIONSERVICE_API SubscriptionNode {
public:
    SubscriptionNode();
    explicit SubscriptionNode(SubscriptionNode* parentNode);
    virtual ~SubscriptionNode();

    SubscriptionNode(const SubscriptionNode&) = delete;
    SubscriptionNode& operator=(const SubscriptionNode&) = delete;
    SubscriptionNode(SubscriptionNode&&) = delete;
    SubscriptionNode& operator=(SubscriptionNode&&) = delete;

    void subscribe(const std::string& commandName, CommandFunction function);
    void unsubscribe(const std::string& commandName, CommandFunction function);

    void signalUCommand(const std::string& commandName, const std::any& data);
    void signalUPacket(const std::string& packetName, const std::any& data);

private:
    friend class NodeManager::Impl;

    class Impl;
    std::unique_ptr<Impl> m_impl;

    std::thread m_implThread;

    asio::io_context m_io;
    asio::executor_work_guard<asio::io_context::executor_type> m_workGuard;
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // SUBSCRIPTIONSERVICE_SUBSCRIPTION_NODE_HPP
