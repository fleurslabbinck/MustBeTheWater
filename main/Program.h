#ifndef PROGRAM_H
#define PROGRAM_H

namespace gg
{
    // Task bootstrapper
    class Program final
    {
    public:
        Program() = default;
        ~Program() = default;
        Program(const Program&) = delete;
        Program(Program&&) = delete;
        Program& operator=(const Program&) = delete;
        Program& operator=(Program&&) = delete;

        void Init() const;
    };
}
#endif