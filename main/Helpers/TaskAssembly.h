#ifndef TASK_ASSEMBLY_H
#define TASK_ASSEMBLY_H

#include <string>

namespace gg
{
    enum class CoreSelect : int8_t
    {
        CoreZero = 0,
        CoreOne = 1,
        None = -1
    };

    struct TaskAssembly
    {
        TaskAssembly()
            : name{std::string("Task: " + std::to_string(totalAssembled)).c_str()}
        {
            ++totalAssembled;
        }

        TaskAssembly(const char* name, uint32_t stackSize, uint8_t priority, CoreSelect core)
            : core{core}, priority(priority), stackSize{stackSize}, name{name}
        {
            ++totalAssembled;
        }

        CoreSelect core{CoreSelect::None};
        uint8_t priority{1};
        uint32_t stackSize{2048};
        const char* name{};

        UBaseType_t GetCoreId() const
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