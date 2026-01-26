#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <string>

#include "Singleton.h"

namespace gg
{
    class LogManager final : public Singleton<LogManager>
    {
    public:
        void Log(const std::string& logMessage);

    private:
        friend class Singleton<LogManager>;
        LogManager() = default;
    };
}
#endif