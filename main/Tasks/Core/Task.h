#ifndef TASK_H
#define TASK_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <atomic>

namespace gg
{
    // Task Base class
    // NOTE: Task wrapper must have static storage duration
    class Task
    {
    public:
        enum class CoreSelect : int8_t
        {
            CoreZero = 0,
            CoreOne = 1,
            None = -1
        };

        Task() = default;
        virtual ~Task();
        Task(const Task&) = delete;
        Task(Task&&) = delete;
        Task& operator=(const Task&) = delete;
        Task& operator=(Task&&) = delete;

        void Suspend();
        void Resume();
        void End();

        TaskHandle_t GetHandle() const {return m_Handle;}

    protected:
        void Init(const char* name, uint32_t stackSize, uint8_t priority, CoreSelect core);
        void Init(const char* name, uint32_t stackSize, uint8_t priority);
        virtual void InitOnStart() {}
        virtual void Execute() = 0;
        virtual bool WaitForWork() = 0;
        virtual void Unblock() = 0;

        bool StopRequested() const {return m_StopRequested.load(std::memory_order_relaxed);}
    
    private:
        std::atomic<bool> m_StopRequested{false};
        TaskHandle_t m_Handle{nullptr};

        static void TaskEntry(void* pvParameters);
        void Run();
    };
}
#endif