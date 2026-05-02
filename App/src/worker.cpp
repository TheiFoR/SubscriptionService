#include "worker.h"

#include <SubscriptionService/logger.hpp>

#include <iostream>
#include <complex>

Worker::Worker(SubscriptionNode *parent)
	: SubscriptionNode(parent)
	, m_timer(io)

{
	NSS::Log::info("Worker", "Worker", "Create");

	subscribe("_Zh^85_start", std::bind(&Worker::handleStartCommand, this, std::placeholders::_1));
	subscribe("_Zh^85_stop", std::bind(&Worker::handleStopCommand, this, std::placeholders::_1));

	NSS::Log::info("Worker", "Worker", "Created");
}

Worker::~Worker()
{
	NSS::Log::info("Worker", "Worker", "Destroy");
	NSS::Log::info("Worker", "Worker", "Destroyed");
}

void Worker::handleStartCommand(const std::any& data) {
	if (!data.has_value()) {
		NSS::Log::warning("Worker", "Handle start command", "Received start command with no data");
		return;
	}

	const int* value = std::any_cast<int>(&data);

	NSS::Log::info("Worker", "Handle start command", "Received start command with value: " + std::to_string(*value));

	if (*value == 0) {
		runMandelbrot();
	} 
	else if (*value == 1) {
		runPi();
	} 
	else {
		NSS::Log::error("Worker", "Handle start command", "Received start command with unknown value: " + std::to_string(*value));
	}
}

void Worker::handleStopCommand(const std::any& data) {
	if (!data.has_value()) {
		NSS::Log::warning("Worker", "Handle stop command", "Received stop command with no data");
		return;
	}

	const int* value = std::any_cast<int>(&data);

	if (value) {
		NSS::Log::info("Worker", "Handle stop command", "Received stop command with value: " + std::to_string(*value));
	} 
	else {
		NSS::Log::error("Worker", "Handle stop command", "Received stop command with data of unexpected type");
		return;
	}
}

void Worker::runPi()
{
    NSS::Log::info("Worker", "Pi", "Start");

    auto state = std::make_shared<PiState>();

    auto step = std::make_shared<std::function<void()>>();

    *step = [this, state, step]()
    {
        for (int i = 0; i < 1'000'000; i++)
        {
            double x = rand() / double(RAND_MAX);
            double y = rand() / double(RAND_MAX);

            if (x * x + y * y <= 1.0)
                state->inside++;

            state->total++;
        }

        double pi = 4.0 * state->inside / state->total;

        std::cout << "[PI] " << pi
                  << " samples=" << state->total << "\n";

        m_timer.expires_after(std::chrono::seconds(1));
        m_timer.async_wait([step](const asio::error_code& ec)
        {
            if (!ec) (*step)();
        });
    };

    (*step)();
}


void Worker::runMandelbrot()
{
    auto state = std::make_shared<MandelState>();

    auto step = std::make_shared<std::function<void()>>();

    *step = [this, state, step]()
    {
        if (state->y >= state->height)
            return;

        std::string line;

        for (int x = 0; x < state->width; x++)
        {
            double cx = (x - state->width / 2.0) * 0.01;
            double cy = (state->y - state->height / 2.0) * 0.01;

            std::complex<double> c(cx, cy);
            std::complex<double> z(0, 0);

            int iter = 0;

            while (abs(z) < 2.0 && iter < 50)
            {
                z = z * z + c;
                iter++;
            }

            line += (iter == 50 ? '#' : '.');
        }

        std::cout << line << "\n";
        state->y++;

        m_timer.expires_after(std::chrono::milliseconds(100));
        m_timer.async_wait([step](const asio::error_code& ec)
        {
            if (!ec) (*step)();
        });
    };

    (*step)();
}
