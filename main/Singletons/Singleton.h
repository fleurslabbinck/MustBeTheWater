#ifndef SINGLETON_H
#define SINGLETON_H

namespace gg
{
    template <typename SingletonType>
    class Singleton
    {
    public:
        virtual ~Singleton() = default;
        Singleton(const Singleton&) = delete;
        Singleton(Singleton&&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton& operator=(Singleton&&) = delete;

        static SingletonType& Get()
        {
            static SingletonType instance{};
            return instance;
        }

    protected:
        Singleton() = default;
    };
}
#endif