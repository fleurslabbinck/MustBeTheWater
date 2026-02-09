#ifndef DATA_PROCESS_TASK_H
#define DATA_PROCESS_TASK_H

#include "Tasks/Core/NotificationTask.h"
#include "Events/Core/Listener.h"

namespace gg
{
    class DataProcessTask : public NotificationTask, public Listener
    {
    public:
        DataProcessTask();
        ~DataProcessTask();
    };
}
#endif