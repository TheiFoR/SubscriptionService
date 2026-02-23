#include <iostream>

#include <subscription_node.hpp>
#include <node_manager.hpp>

#include <asio/io_context.hpp>

#include <any>

class SS1 : public SubscriptionNode {
public:
	SS1() {
		std::cout << "SS1 initialized." << std::endl;

		subscribe("TestCommand1", std::bind(&SS1::handleTestCommand1, this, std::placeholders::_1));

		signalUCommand("TestCommand1", 1);
		signalUPacket("TestPacket1", std::string("1 Hello, World!"));
	}

	void handleTestCommand1(const std::any& data) {
		std::cout << "Handling TestCommand1 with data: " << std::any_cast<int>(data) << std::endl;
	}
};

class SS2 : public SubscriptionNode {
public:
	SS2() {
		std::cout << "SS2 initialized." << std::endl;

		subscribe("TestCommand2", std::bind(&SS2::handleTestCommand2, this, std::placeholders::_1));

		signalUCommand("TestCommand2", 2);
		signalUPacket("TestPacket2", std::string("2 Hello, World!"));
	}

	void handleTestCommand2(const std::any& data) {
		std::cout << "Handling TestCommand2 with data: " << std::any_cast<int>(data) << std::endl;
	}
};

int main()
{
	asio::io_context io;

	// ==========
	NodeManager manager;

	SS1 ss1;
	SS2 ss2;

	manager.addNode(&ss1);
	manager.addNode(&ss2);

	// ==========

	auto work = asio::make_work_guard(io);
	io.run();

	return 0;
}
