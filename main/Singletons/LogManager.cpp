#include "LogManager.h"

#include <iostream>

namespace gg
{
    void LogManager::Log(const std::string& logMessage)
    {
        std::cout << logMessage;
    }
}