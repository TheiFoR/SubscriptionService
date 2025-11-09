#ifndef SUBSCRIPTION_SERVICE_TYPES_H
#define SUBSCRIPTION_SERVICE_TYPES_H

#include <functional>
#include <QVariantMap>

namespace subscriptionservice{

using CallbackCommandFunction = std::function<void(const QVariantMap&)>;
using CallbackPacketFunction = std::function<void(const QString&, const QVariantMap&)>;

} // subscriptionservice

#endif // SUBSCRIPTION_SERVICE_TYPES_H
