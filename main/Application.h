#ifndef APPLICATION_H
#define APPLICATION_H

namespace gg
{
    // Task bootstrapper
    class Application final
    {
    public:
        Application() = default;
        ~Application() = default;
        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;

        void Init() const;
    };
}
#endif