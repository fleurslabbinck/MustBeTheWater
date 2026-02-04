#ifndef BLINKER_H
#define BLINKER_H

#include "Components/Component.h"

namespace gg
{
    class Led final : public Component
    {
    public:
        Led(uint8_t gpioPin);
        ~Led() = default;
        Led(const Led&) = delete;
        Led(Led&&) = delete;
        Led& operator=(const Led&) = delete;
        Led& operator=(Led&&) = delete;

        void TurnOn();
        void TurnOff();

    private:
        bool m_On{false};
        static const std::string m_OnMessage;
        static const std::string m_OffMessage;
    };
}
#endif