#ifndef ESP_H
#define ESP_H

namespace gg
{
    class Esp final
    {
    public:
        explicit Esp();
        ~Esp() = default;
        Esp(const Esp&) = delete;
        Esp(Esp&&) = delete;
        Esp& operator=(const Esp&) = delete;
        Esp& operator=(Esp&&) = delete;

        void Run();

    private:
        bool m_Quit{false};
    };
}
#endif