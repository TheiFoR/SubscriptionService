#ifndef SUBSCRIPTIONSERVICE_INTERNAL_SUBSCRIPTION_NODE_IMPL_HPP
#define SUBSCRIPTIONSERVICE_INTERNAL_SUBSCRIPTION_NODE_IMPL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "SubscriptionService/subscription_node.hpp"

#include <asio/io_context.hpp>
#include <asio/strand.hpp>

#include <memory>
#include <mutex>
#include <set>
#include <unordered_map>
#include <vector>
#include <queue>

class NodeManager;

class SubscriptionNode::Impl {
public:
    explicit Impl(SubscriptionNode* parent = nullptr);
    ~Impl();

    void subscribe(const std::string& commandName, CommandFunction function);
    void unsubscribe(const std::string& commandName, const CommandFunction& function);

    void signalUCommand(const std::string& commandName, const std::any& data);
    void signalUPacket(const std::string& packetName, const std::any& data) const;

    void setNodeManager(NodeManager* manager);

private:
    SubscriptionNode* m_parent = nullptr;
    NodeManager* m_nodeManager = nullptr;

    std::queue<Packet> m_pendingPackets;
    
};

#endif // SUBSCRIPTIONSERVICE_INTERNAL_SUBSCRIPTION_NODE_IMPL_HPP
