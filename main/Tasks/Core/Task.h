#ifndef TASK_H
#define TASK_H

#include <atomic>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Helpers/TaskConfig.h"

namespace gg
{
    // Task Base class
    // NOTE: Task wrapper must have static storage duration
    class Task
    {
    public:
        Task() = default;
        virtual ~Task();
        Task(const Task&) = delete;
        Task(Task&&) = delete;
        Task& operator=(const Task&) = delete;
        Task& operator=(Task&&) = delete;

        void PinToCore(CoreSelect core);

        void Suspend();
        void Resume();
        void End();

        TaskHandle_t GetHandle() const {return m_Handle;}

    protected:
        void CreateTask(const TaskConfig& taskConfig);
        virtual void InitOnStart() {}
        virtual void Execute() = 0;
        virtual bool WaitForWork() = 0;
        virtual void Unblock() = 0;

        bool StopRequested() const {return m_StopRequested.load(std::memory_order_relaxed);}
    
    private:
        BaseType_t m_Core{tskNO_AFFINITY};
        std::atomic<bool> m_StopRequested{false};
        TaskHandle_t m_Handle{nullptr};

        static void TaskEntry(void* args);
        void Run();
    };
}
#endif