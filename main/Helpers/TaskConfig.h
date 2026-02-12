#ifndef TASK_CONFIG_H
#define TASK_CONFIG_H

#include <string>

namespace gg
{
    enum class CoreSelect : int
    {
        CoreZero = 0,
        CoreOne = 1,
        None = tskNO_AFFINITY
    };

    struct TaskConfig
    {
        explicit TaskConfig()
            : TaskConfig(std::string("Task: " + std::to_string(totalAssembled)))
        {}

        explicit TaskConfig(const std::string& name)
            : name{name.c_str()}
        {
            ++totalAssembled;
        }

        uint8_t priority{1};
        uint32_t stackSize{2048};
        const char* name;

        static BaseType_t GetCoreId(CoreSelect core)
        {
            BaseType_t coreId{static_cast<BaseType_t>(core)};
            if (core == CoreSelect::None)
            {
                coreId = tskNO_AFFINITY;
            }

            return coreId;
        }

    private:
        inline static uint8_t totalAssembled{};
    };
}
#endif