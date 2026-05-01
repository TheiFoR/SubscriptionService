#include "core.h"

#include <SubscriptionService/logger.hpp>

#include <asio/dispatch.hpp>

Core::Core()
	: SubscriptionNode()
{
	NSS::Log::info("Core", "Core", "Create");

	m_mandelbrodNoiseThread = std::thread([this](){
		m_mandelbrodNoiseWorker = std::make_unique<Worker>(this);
		m_nodeManager.addNode(m_mandelbrodNoiseWorker.get());
		m_mandelbrodNoiseWorker->io.run();
	});

	m_piCalcThread = std::thread([this](){
		m_piCalcWorker = std::make_unique<Worker>(this);
		m_nodeManager.addNode(m_piCalcWorker.get());
		m_piCalcWorker->io.run();
	});

	m_nodeManager.addNode(this);

	signalUCommand("_Zh^85_start", 0);

	NSS::Log::info("Core", "Core", "Created");
}

Core::~Core()
{
	NSS::Log::info("Core", "Core", "Destroy");
	NSS::Log::info("Core", "Core", "Destroyed");
}