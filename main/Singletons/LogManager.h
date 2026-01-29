#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <string>

#include "Singleton.h"

namespace gg
{
    class LogManager final : public Singleton<LogManager>
    {
    public:
        LogManager(const LogManager&) = delete;
        LogManager(LogManager&&) = delete;
        LogManager& operator=(const LogManager&) = delete;
        LogManager& operator=(LogManager&&) = delete;

        void Log(const std::string& message) const;
        void Log(const std::string& id, const std::string& messsage) const;

    private:
        friend class Singleton<LogManager>;
        LogManager() = default;
    };
}
#endif