#ifndef CORE_H
#define CORE_H

#include <SubscriptionService/node_manager.hpp>
#include <SubscriptionService/subscription_node.hpp>

#include <thread>
#include <memory>

#include "worker.h"

class Core : public SubscriptionNode 
{
public:
    Core();
    ~Core() override;

private:
    std::unique_ptr<Worker> m_mandelbrodNoiseWorker;
    std::unique_ptr<Worker> m_piCalcWorker;

    std::thread m_mandelbrodNoiseThread;
    std::thread m_piCalcThread;

    NodeManager m_nodeManager;
};

#endif // CORE_H