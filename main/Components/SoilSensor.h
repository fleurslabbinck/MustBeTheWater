#ifndef SOIL_SENSOR_H
#define SOIL_SENSOR_H

#include "Components/Component.h"

namespace gg
{
    class SoilSensor final : public Component
    {
    public:
        SoilSensor(uint8_t gpioPin);
        ~SoilSensor() = default;
        SoilSensor(const SoilSensor&) = delete;
        SoilSensor(SoilSensor&&) = delete;
        SoilSensor& operator=(const SoilSensor&) = delete;
        SoilSensor& operator=(SoilSensor&&) = delete;

    private:

    };
}
#endif