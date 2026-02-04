#include "SoilSensor.h"

#include "esp_adc/adc_cali.h"

namespace gg
{
    SoilSensor::SoilSensor(uint8_t gpioPin)
        : Component(gpioPin)
    {
        
    }
}