#include "SubscriptionService/subscription_node.hpp"

#include "SubscriptionService/logger.hpp"
#include "SubscriptionService/node_manager.hpp"
#include "internal/subscription/subscription_node_impl.hpp"

#include <future>

SubscriptionNode::SubscriptionNode()
    : m_workGuard(asio::make_work_guard(m_io))
{
    NSS::Log::info("SubscriptionNode", "Core", "Create without parent");

    std::promise<void> initPromise;
    std::future<void> initFuture = initPromise.get_future();

    m_implThread = std::thread([this, promise = std::move(initPromise)]() mutable {
        try {
            m_impl = std::make_unique<Impl>();
            promise.set_value();
            m_io.run();
        } catch (const std::exception& ex) {
            NSS::Log::error("SubscriptionNode", "Core", std::string("Exception in SubscriptionNode thread: ") + ex.what());
        } catch (...) {
            NSS::Log::error("SubscriptionNode", "Core", "Unknown exception in SubscriptionNode thread");
        }
    });

    initFuture.get();

    NSS::Log::info("SubscriptionNode", "Core", "Created without parent");
}

SubscriptionNode::SubscriptionNode(SubscriptionNode* parentNode)
    : m_workGuard(asio::make_work_guard(m_io))
{
    NSS::Log::info("SubscriptionNode", "Core", "Create with parent");

    std::promise<void> initPromise;
    std::future<void> initFuture = initPromise.get_future();

    m_implThread = std::thread([this, parentNode, promise = std::move(initPromise)]() mutable {
        try {
            m_impl = std::make_unique<Impl>(parentNode);
            promise.set_value();
            m_io.run();
        } catch (const std::exception& ex) {
            NSS::Log::error("SubscriptionNode", "Core", std::string("Exception in SubscriptionNode thread: ") + ex.what());
        } catch (...) {
            NSS::Log::error("SubscriptionNode", "Core", "Unknown exception in SubscriptionNode thread");
        }
    });

    initFuture.get();

    NSS::Log::info("SubscriptionNode", "Core", "Created with parent");
}

SubscriptionNode::~SubscriptionNode() {
    NSS::Log::info("SubscriptionNode", "Core", "Destroy");
    NSS::Log::info("SubscriptionNode", "Core", "Destroyed");
}

void SubscriptionNode::subscribe(const std::string& commandName, CommandFunction function) {
    m_impl->subscribe(commandName, std::move(function));
}

void SubscriptionNode::unsubscribe(const std::string& commandName, CommandFunction function) {
    m_impl->unsubscribe(commandName, std::move(function));
}

void SubscriptionNode::signalUCommand(const std::string& commandName, const std::any& data) {
    m_impl->signalUCommand(commandName, data);
}

void SubscriptionNode::signalUPacket(const std::string& packetName, const std::any& data) {
    m_impl->signalUPacket(packetName, data);
}