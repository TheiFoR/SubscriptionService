#ifndef WORKER_H
#define WORKER_H

#include <SubscriptionService/subscription_node.hpp>

#include <asio/io_context.hpp>
#include <asio/steady_timer.hpp>

#include <any>

class Worker : public SubscriptionNode 
{
public:
    explicit Worker(SubscriptionNode *parent);
    ~Worker() override;

    asio::io_context io;

private:
    struct PiState
    {
        uint64_t inside = 0;
        uint64_t total = 0;
    };
    struct MandelState
    {
        int y = 0;
        int width = 120;
        int height = 40;
    };


    void handleStartCommand(const std::any& data);
    void handleStopCommand(const std::any& data);

    void runPi();
    void runMandelbrot();
    
    asio::steady_timer m_timer;
};

#endif // WORKER_H