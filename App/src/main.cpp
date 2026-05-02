#include <asio/io_context.hpp>
#include <asio/executor_work_guard.hpp>

#include <SubscriptionService/logger.hpp>

#include "core.h"

// class SS3 : public SubscriptionNode {
// public:
// 	explicit SS3(SubscriptionNode* parentNode) : SubscriptionNode(parentNode)
// 	{
// 		NSS::NSS::Log::info("SS3", "Core", "Initialized");

// 		subscribe("TestCommand1", std::bind(&SS3::handleTestCommand1, this, std::placeholders::_1));

// 		signalUCommand("TestCommand3", 3);
// 		// signalUPacket("TestPacket3", std::string("3 Hello, World!"));
// 	}

// 	void handleTestCommand1(const std::any& data) {
// 		NSS::NSS::Log::info("SS3", "C1", "Handling TestCommand1 with data: " + std::to_string(std::any_cast<int>(data)));
// 	}
// };

// class SS1 : public SubscriptionNode {
// public:
// 	SS1() : SubscriptionNode()
// 	{
// 		NSS::NSS::Log::info("SS1", "Core", "Initialized");

// 		subscribe("TestCommand1", std::bind(&SS1::handleTestCommand1, this, std::placeholders::_1));
// 		subscribe("TestCommand3", std::bind(&SS1::handleTestCommand3, this, std::placeholders::_1));

// 		signalUCommand("TestCommand1", 1);
// 		// signalUPacket("TestPacket1", std::string("1 Hello, World!"));
// 	}

// 	void handleTestCommand1(const std::any& data) {
// 		NSS::NSS::Log::info("SS1", "C1", "Handling TestCommand1 with data: " + std::to_string(std::any_cast<int>(data)));
// 	}
// 	void handleTestCommand3(const std::any& data) {
// 		NSS::NSS::Log::info("SS1", "C3", "Handling TestCommand3 with data: " + std::to_string(std::any_cast<int>(data)));
// 	}
// };

// class SS2 : public SubscriptionNode {
// public:
// 	SS2(SubscriptionNode* parentNode)
// 		: SubscriptionNode(parentNode)
// 		, ss3(this)
// 	{
// 		NSS::NSS::Log::info("SS2", "Core", "Initialized");

// 		subscribe("TestCommand2", std::bind(&SS2::handleTestCommand2, this, std::placeholders::_1));

// 		signalUCommand("TestCommand2", 2);
// 		// signalUPacket("TestPacket2", std::string("2 Hello, World!"));
// 	}

// 	void handleTestCommand2(const std::any& data) {
// 		NSS::NSS::Log::info("SS2", "C2", "Handling TestCommand2 with data: " + std::to_string(std::any_cast<int>(data)));
// 	}

// private:
// 	SS3 ss3;
// };

// class SS4 : public SubscriptionNode {
// public:	
// 	SS4() 
// 		: SubscriptionNode()
// 		, ss2(this)
// 	{
// 		NSS::NSS::Log::info("SS4", "Core", "Initialized");

// 		subscribe("TestCommand1", std::bind(&SS4::handleTestCommand1, this, std::placeholders::_1));

// 		signalUCommand("TestCommand1", 4);
// 		// signalUPacket("TestPacket1", std::string("4 Hello, World!"));
// 	}

// 	void handleTestCommand1(const std::any& data) {
// 		NSS::NSS::Log::info("SS4", "C1", "Handling TestCommand1 with data: " + std::to_string(std::any_cast<int>(data)));
// 	}

// private:
// 	SS2 ss2;
// };

int main()
{
	asio::io_context ioContext;
	asio::executor_work_guard<asio::io_context::executor_type> workGuard(ioContext.get_executor());

	Core core{};

	// NodeManager manager;

	// SS1 ss1;
	// SS4 ss4;

	// manager.addNode(&ss1);
	// manager.addNode(&ss4);

	// NSS::NSS::Log::info("Main", "Tree", "SS1 direct children: " + std::to_string(ss1.getChildren().size()));
	// NSS::NSS::Log::info("Main", "Tree", "SS4 direct children: " + std::to_string(ss4.getChildren().size()));

	ioContext.run();

	return 0;
}
