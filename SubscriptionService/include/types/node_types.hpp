#ifndef SUBSCRIPTION_NODE_TYPES_HPP
#define SUBSCRIPTION_NODE_TYPES_HPP

#include <functional>
#include <any>
#include <string>

using CommandFunction = std::function<void(const std::any&)>;
using PacketFunction = std::function<void(const std::string&, const std::any&)>;

#endif // SUBSCRIPTION_NODE_TYPES_HPP