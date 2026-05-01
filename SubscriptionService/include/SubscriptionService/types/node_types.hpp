#ifndef SUBSCRIPTION_NODE_TYPES_HPP
#define SUBSCRIPTION_NODE_TYPES_HPP

#include <functional>
#include <any>
#include <string>
#include <typeindex>

using CommandFunction = std::function<void(const std::any&)>;
using PacketFunction = std::function<void(const std::string&, const std::any&)>;

struct Packet {
    std::string name;
    std::any data;
    std::type_index type;
}

#endif // SUBSCRIPTION_NODE_TYPES_HPP
