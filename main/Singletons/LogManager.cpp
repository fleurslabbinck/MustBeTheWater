#include "LogManager.h"

#include <iostream>

namespace gg
{
    void LogManager::Log(const std::string& message)
    {
        std::cout << message << std::endl;
    }

    void LogManager::Log(const std::string& id, const std::string& message)
    {
        std::cout << id << " " << message << std::endl;
    }
}