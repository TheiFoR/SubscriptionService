#include "internal/subscription/subscription_node_impl.hpp"
#include "SubscriptionService/subscription_node.hpp"
#include "SubscriptionService/internal/node_manager_impl.hpp"

#include "SubscriptionService/logger.hpp"

#include <asio/executor_work_guard.hpp>
#include <asio/post.hpp>

#include <algorithm>
#include <future>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

SubscriptionNode::Impl::Impl(SubscriptionNode* parent) 
{
    NSS::Log::info("SubscriptionNodeImpl", "Core", "Create");

    m_parent = parent;

    NSS::Log::info("SubscriptionNodeImpl", "Core", "Created");
}

SubscriptionNode::Impl::~Impl()
{
    NSS::Log::info("SubscriptionNodeImpl", "Core", "Destroy");
    NSS::Log::info("SubscriptionNodeImpl", "Core", "Destroyed");
}

void SubscriptionNode::Impl::subscribe(const std::string& commandName, CommandFunction function) {
    (void)commandName;
    (void)function;
    NSS::Log::info("SubscriptionNodeImpl", "Subscribe", "Subscribing to command <" + commandName + ">");
}

void SubscriptionNode::Impl::unsubscribe(const std::string& commandName, const CommandFunction& function) {
    (void)commandName;
    (void)function;
    NSS::Log::info("SubscriptionNodeImpl", "Unsubscribe", "Unsubscribing from command <" + commandName + ">");
}

void SubscriptionNode::Impl::signalUCommand(const std::string& commandName, const std::any& data) {
    (void)commandName;
    (void)data;
    NSS::Log::info("SubscriptionNodeImpl", "SignalUCommand", "Signaling command <" + commandName + "> with data of type <" + std::string(data.type().name()) + ">");
}

void SubscriptionNode::Impl::signalUPacket(const std::string& packetName, const std::any& data) const {
    (void)packetName;
    (void)data;
    NSS::Log::info("SubscriptionNodeImpl", "SignalUPacket", "Signaling packet <" + packetName + "> with data of type <" + std::string(data.type().name()) + ">");
}

void SubscriptionNode::Impl::setNodeManager(NodeManager::Impl* manager) {
    m_nodeManager = manager;
    NSS::Log::info("SubscriptionNodeImpl", "SetNodeManager", "Node manager set for node");
}