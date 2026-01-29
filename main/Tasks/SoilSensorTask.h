#ifndef SOILSENSORTASK_H
#define SOILSENSORTASK_H

#include "Tasks/NotificationTask.h"
#include "Components/Led.h"

namespace gg
{
    class SoilSensorTask final : public NotificationTask
    {
    public:
        SoilSensorTask();
        SoilSensorTask(const SoilSensorTask&) = delete;
        SoilSensorTask(SoilSensorTask&&) = delete;
        SoilSensorTask& operator=(const SoilSensorTask&) = delete;
        SoilSensorTask& operator=(SoilSensorTask&&) = delete;

        void Start();

    private:
        bool m_Blink{false};
        Led m_Led;

        void Execute() override;
    };
}
#endif