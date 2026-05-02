#include "SubscriptionService/node_manager.hpp"
#include "SubscriptionService/logger.hpp"

#include "internal/node_manager_impl.hpp"

#include <asio/post.hpp>

#include <future>

NodeManager::NodeManager() {
    NSS::Log::info("NodeManager", "Core", "Create");

    std::promise<void> initPromise;
    std::future<void> initFuture = initPromise.get_future();

    m_implThread = std::thread([this, promise = std::move(initPromise)]() mutable {
        try {
            m_impl = std::make_unique<Impl>();
            promise.set_value();
            m_impl->io.run();
        } catch (const std::exception& ex) {
            NSS::Log::error("NodeManager", "Core", std::string("Exception in NodeManager thread: ") + ex.what());
        } catch (...) {
            NSS::Log::error("NodeManager", "Core", "Unknown exception in NodeManager thread");
        }
    });

    initFuture.get();

    NSS::Log::info("NodeManager", "Core", "Created");
}

NodeManager::~NodeManager() {
    NSS::Log::info("NodeManager", "Core", "Destroy");
    
    if (m_impl) {
        m_impl->io.stop();
    }
    if (m_implThread.joinable()) {
        m_implThread.join();
    }

    NSS::Log::info("NodeManager", "Core", "Destroyed");
}

void NodeManager::addNode(const SubscriptionNode* node) {
    if (node == nullptr) {
        NSS::Log::error("NodeManager", "AddNode", "Cannot add node: node pointer is null");
        return;
    }

    asio::post(m_impl->io, [this, node]() {
        m_impl->addNode(node);
    });
}

void NodeManager::removeNode(const SubscriptionNode* node) {
    if (node == nullptr) {
        NSS::Log::error("NodeManager", "RemoveNode", "Cannot remove node: node pointer is null");
        return;
    }

    asio::post(m_impl->io, [this, node]() {
        m_impl->removeNode(node);
    });
}

// void NodeManager::addNode(const SubscriptionNode* node) {
//     NSS::Log::info("NodeManager", "AddNode", "Adding node and its descendants...");

//     if (node == nullptr) {
//         NSS::Log::error("NodeManager", "AddNode", "Cannot add node: node pointer is null");
//         return;
//     }

//     std::vector<SubscriptionNode*> insertedNodes;
//     std::vector<SubscriptionNode*> stack{ const_cast<SubscriptionNode*>(node) };

//     while (!stack.empty()) {
//         SubscriptionNode* current = stack.back();
//         stack.pop_back();

//         if (current == nullptr) {
//             continue;
//         }

//         bool inserted = false;
//         {
//             std::unique_lock nodesLock(m_nodesMutex);
//             inserted = m_nodes.insert(current).second;
//         }

//         current->m_impl->attachManager(this);

//         if (inserted) {
//             insertedNodes.push_back(current);
//         }

//         const std::vector<SubscriptionNode*> children = current->m_impl->getChildrenSnapshot();
//         stack.insert(stack.end(), children.begin(), children.end());
//     }

//     for (SubscriptionNode* current : insertedNodes) {
//         if (current == nullptr) {
//             continue;
//         }

//         const auto subscriptions = current->m_impl->getSubscriptionsSnapshot();
//         for (const auto& [commandName, handler] : subscriptions) {
//             subscribe(current, commandName, handler);
//         }
//     }

//     for (SubscriptionNode* current : insertedNodes) {
//         if (current == nullptr) {
//             continue;
//         }

//         auto pendingCommands = current->m_impl->takePendingCommands();
//         for (auto& [commandName, payload] : pendingCommands) {
//             publishCommand(current, commandName, std::move(payload));
//         }
//     }
//     NSS::Log::info("NodeManager", "AddNode", "Added node and its descendants: " + std::to_string(insertedNodes.size()) + " nodes added");
// }

// void NodeManager::removeNode(const SubscriptionNode* node) {
//     if (node == nullptr) {
//         NSS::Log::error("NodeManager", "RemoveNode", "Cannot remove node: node pointer is null");
//         return;
//     }

//     std::vector<SubscriptionNode*> stack{ const_cast<SubscriptionNode*>(node) };
//     std::vector<SubscriptionNode*> removedNodes;

//     while (!stack.empty()) {
//         SubscriptionNode* current = stack.back();
//         stack.pop_back();

//         if (current == nullptr) {
//             continue;
//         }

//         removedNodes.push_back(current);

//         const std::vector<SubscriptionNode*> children = current->m_impl->getChildrenSnapshot();
//         stack.insert(stack.end(), children.begin(), children.end());
//     }

//     {
//         std::scoped_lock lock(m_nodesMutex, m_subscriptionsMutex);
//         for (SubscriptionNode* current : removedNodes) {
//             m_nodes.erase(current);
//         }

//         for (auto it = m_subscriptions.begin(); it != m_subscriptions.end();) {
//             auto& handlers = it->second;
//             handlers.erase(
//                 std::remove_if(
//                     handlers.begin(),
//                     handlers.end(),
//                     [&](const SubscriptionRecord& record) {
//                         return std::find(removedNodes.begin(), removedNodes.end(), const_cast<SubscriptionNode*>(record.node)) != removedNodes.end();
//                     }),
//                 handlers.end());

//             if (handlers.empty()) {
//                 it = m_subscriptions.erase(it);
//                 continue;
//             }

//             ++it;
//         }
//     }

//     for (SubscriptionNode* current : removedNodes) {
//         if (current != nullptr) {
//             current->m_impl->detachManagerIfMatches(this);
//         }
//     }
// }

// void NodeManager::subscribe(const SubscriptionNode* node, const std::string& commandName, CommandFunction function) {
//     if (node == nullptr) {
//         NSS::Log::error("NodeManager", "Subscribe", "Cannot subscribe: node pointer is null");
//         return;
//     }
//     if (commandName.empty()) {
//         NSS::Log::error("NodeManager", "Subscribe", "Cannot subscribe: command name is empty");
//         return;
//     }
//     if (!function) {
//         NSS::Log::error("NodeManager", "Subscribe", "Cannot subscribe: handler is empty");
//         return;
//     }

//     {
//         std::unique_lock nodesLock(m_nodesMutex);
//         m_nodes.insert(node);
//     }

//     std::unique_lock subscriptionsLock(m_subscriptionsMutex);
//     m_subscriptions[commandName].push_back(SubscriptionRecord{ node, std::move(function) });
// }

// void NodeManager::unsubscribe(const SubscriptionNode* node, const std::string& commandName, const CommandFunction& function) {
//     if (node == nullptr) {
//         NSS::Log::error("NodeManager", "Unsubscribe", "Cannot unsubscribe: node pointer is null");
//         return;
//     }
//     if (commandName.empty()) {
//         NSS::Log::error("NodeManager", "Unsubscribe", "Cannot unsubscribe: command name is empty");
//         return;
//     }
//     if (!function) {
//         NSS::Log::error("NodeManager", "Unsubscribe", "Cannot unsubscribe: handler is empty");
//         return;
//     }

//     std::unique_lock lock(m_subscriptionsMutex);
//     auto it = m_subscriptions.find(commandName);
//     if (it == m_subscriptions.end()) {
//         NSS::Log::error("NodeManager", "Unsubscribe", "Cannot unsubscribe: command was not found: " + commandName + '.');
//         return;
//     }

//     auto& handlers = it->second;
//     handlers.erase(
//         std::remove_if(
//             handlers.begin(),
//             handlers.end(),
//             [&](const SubscriptionRecord& record) {
//                 if (record.node != node) {
//                     return false;
//                 }

//                 return record.handler.target_type() == function.target_type();
//             }),
//         handlers.end());

//     if (handlers.empty()) {
//         m_subscriptions.erase(it);
//     }
// }

// void NodeManager::publishCommand(const SubscriptionNode* sourceNode, const std::string& commandName, std::shared_ptr<const std::any> data) {
//     (void)sourceNode;
//     if (commandName.empty()) {
//         NSS::Log::error("NodeManager", "PublishCommand", "Cannot publish command: command name is empty");
//         return;
//     }
//     if (data == nullptr) {
//         NSS::Log::error("NodeManager", "PublishCommand", "Cannot publish command: payload data is null");
//         return;
//     }

//     std::vector<SubscriptionRecord> subscribers;
//     {
//         std::shared_lock lock(m_subscriptionsMutex);
//         auto it = m_subscriptions.find(commandName);
//         if (it == m_subscriptions.end()) {
//             return;
//         }
//         subscribers = it->second;
//     }

//     for (const SubscriptionRecord& record : subscribers) {
//         if (record.node == nullptr || !record.handler) {
//             continue;
//         }

//         const SubscriptionNode* targetNode = record.node;
//         CommandFunction handler = record.handler;
//         targetNode->m_impl->dispatchCommand([handler = std::move(handler), data]() {
//             handler(*data);
//         });
//     }
// }

// std::vector<const SubscriptionNode*> NodeManager::getNodes() const {
//     std::shared_lock lock(m_nodesMutex);
//     return std::vector<const SubscriptionNode*>(m_nodes.begin(), m_nodes.end());
// }

// std::size_t NodeManager::getNodeCount() const {
//     std::shared_lock lock(m_nodesMutex);
//     return m_nodes.size();
// }

// std::vector<const SubscriptionNode*> NodeManager::collectDirectChildren(const SubscriptionNode* node) const {
//     std::vector<const SubscriptionNode*> result;
//     if (node == nullptr) {
//         NSS::Log::error("NodeManager", "CollectDirectChildren", "Cannot collect direct children: node pointer is null");
//         return result;
//     }

//     const std::vector<SubscriptionNode*> children = node->m_impl->getChildrenSnapshot();
//     result.reserve(children.size());
//     for (SubscriptionNode* child : children) {
//         result.push_back(child);
//     }

//     return result;
// }

// std::vector<const SubscriptionNode*> NodeManager::collectAllDescendants(const SubscriptionNode* node) const {
//     std::vector<const SubscriptionNode*> result;
//     if (node == nullptr) {
//         NSS::Log::error("NodeManager", "CollectAllDescendants", "Cannot collect descendants: node pointer is null");
//         return result;
//     }

//     std::set<const SubscriptionNode*> visited;
//     std::vector<const SubscriptionNode*> stack = collectDirectChildren(node);

//     while (!stack.empty()) {
//         const SubscriptionNode* current = stack.back();
//         stack.pop_back();

//         if (current == nullptr) {
//             continue;
//         }
//         if (!visited.insert(current).second) {
//             continue;
//         }

//         result.push_back(current);

//         const std::vector<const SubscriptionNode*> children = collectDirectChildren(current);
//         stack.insert(stack.end(), children.begin(), children.end());
//     }

//     return result;
// }
