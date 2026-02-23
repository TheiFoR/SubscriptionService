#include "node_manager.hpp"

#include <iostream>

NodeManager::NodeManager() {
    std::cout << "NodeManager initialized." << std::endl;
}

NodeManager::~NodeManager() {
    std::cout << "NodeManager destroyed." << std::endl;
}

void NodeManager::addNode(const SubscriptionNode* node) {
    std::cout << "Node added to NodeManager." << std::endl;
}