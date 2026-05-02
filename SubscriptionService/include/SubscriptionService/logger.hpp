#ifndef SUBSCRIPTION_LOGGER_HPP
#define SUBSCRIPTION_LOGGER_HPP

#ifdef _WIN32
#ifdef SUBSCRIPTIONSERVICE_EXPORTS
#define SUBSCRIPTIONSERVICE_API __declspec(dllexport)
#else
#define SUBSCRIPTIONSERVICE_API __declspec(dllimport)
#endif
#else
#define SUBSCRIPTIONSERVICE_API [[gnu::visibility("default")]]
#endif

#include <mutex>
#include <string_view>

namespace NSS{

enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warning,
    Error
};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

class SUBSCRIPTIONSERVICE_API Log {
public:
    static void trace(std::string_view className, std::string_view subClass, std::string_view message);
    static void debug(std::string_view className, std::string_view subClass, std::string_view message);
    static void info(std::string_view className, std::string_view subClass, std::string_view message);
    static void warning(std::string_view className, std::string_view subClass, std::string_view message);
    static void error(std::string_view className, std::string_view subClass, std::string_view message);

private:
    static Log& instance();

    Log() = default;
    void log(LogLevel level, std::string_view className, std::string_view subClass, std::string_view message);

    std::string trimClassName(std::string_view className) const;
    std::string trimSubClassName(std::string_view subClass) const;
    std::string trimThreadId(std::string_view threadId) const;

    static size_t s_currentTrimClassNameLength;
    static size_t s_currentTrimSubClassNameLength;
    static size_t s_currentTrimThreadIdLength;

    std::mutex m_outputMutex;
};

}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // SUBSCRIPTION_LOGGER_HPP
