#include "subscription_node.hpp"

#include <iostream>

SubscriptionNode::SubscriptionNode() {
    std::cout << "SubscriptionNode initialized." << std::endl;
}

SubscriptionNode::~SubscriptionNode() {
    std::cout << "SubscriptionNode destroyed." << std::endl;
}

void SubscriptionNode::subscribe(const std::string& commandName, CommandFunction function) {
    std::cout << "Subscribed to command: " << commandName << std::endl;
}

void SubscriptionNode::unsubscribe(const std::string& commandName, CommandFunction function) {
    std::cout << "Unsubscribed from command: " << commandName << std::endl;
}

void SubscriptionNode::signalUCommand(const std::string& commandName, const std::any& data) {
    std::cout << "Signaled command: " << commandName << " with data." << std::endl;
}

void SubscriptionNode::signalUPacket(const std::string& packetName, const std::any& data) {
    std::cout << "Signaled packet: " << packetName << " with data." << std::endl;
}