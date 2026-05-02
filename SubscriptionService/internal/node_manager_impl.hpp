#ifndef SUBSCRIPTIONSERVICE_INTERNAL_NODE_MANAGER_IMPL_HPP
#define SUBSCRIPTIONSERVICE_INTERNAL_NODE_MANAGER_IMPL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include "SubscriptionService/node_manager.hpp"
#include "SubscriptionService/subscription_node.hpp"

#include <asio/executor_work_guard.hpp>
#include <asio/io_context.hpp>

class NodeManager::Impl {
public:
    Impl();
    ~Impl();

    void addNode(const SubscriptionNode* node);
    void removeNode(const SubscriptionNode* node);

    asio::io_context io;
    asio::executor_work_guard<asio::io_context::executor_type> workGuard;
};

#endif // SUBSCRIPTIONSERVICE_INTERNAL_NODE_MANAGER_IMPL_HPP