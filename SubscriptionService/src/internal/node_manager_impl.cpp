#include "internal/node_manager_impl.hpp"

#include "SubscriptionService/internal/subscription/subscription_node_impl.hpp"
#include "SubscriptionService/node_manager.hpp"
#include "SubscriptionService/logger.hpp"

#include <typeinfo>

NodeManager::Impl::Impl()
    : workGuard(asio::make_work_guard(io)) {
    NSS::Log::info("NodeManagerImpl", "Core", "Create");
    NSS::Log::info("NodeManagerImpl", "Core", "Created");
}

NodeManager::Impl::~Impl() {
    NSS::Log::info("NodeManagerImpl", "Core", "Destroy");
    NSS::Log::info("NodeManagerImpl", "Core", "Destroyed");
}

void NodeManager::Impl::addNode(const SubscriptionNode* node) {
    if (node == nullptr) {
        NSS::Log::error("NodeManagerImpl", "AddNode", "Cannot add node: node pointer is null");
        return;
    }

    asio::post(node->m_io, [this, node]() {
        try {
            node->m_impl->setNodeManager(this);
        } catch (const std::exception& ex) {
            NSS::Log::error("NodeManagerImpl", "AddNode", std::string("Exception while adding node: ") + ex.what());
        } catch (...) {
            NSS::Log::error("NodeManagerImpl", "AddNode", "Unknown exception while adding node");
        }
    });

    NSS::Log::info("NodeManagerImpl", "AddNode", "Adding node <" + std::string(typeid(*node).name()) + ">");
}

void NodeManager::Impl::removeNode(const SubscriptionNode* node) {
    if (node == nullptr) {
        NSS::Log::error("NodeManagerImpl", "RemoveNode", "Cannot remove node: node pointer is null");
        return;
    }

    NSS::Log::info("NodeManagerImpl", "RemoveNode", "Removing node <" + std::string(typeid(*node).name()) + ">");
}