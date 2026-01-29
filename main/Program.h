#ifndef PROGRAM_H
#define PROGRAM_H

#include "Tasks/SoilSensorTask.h"

namespace gg
{
    class Program final
    {
    public:
        Program() = default;
        ~Program() = default;
        Program(const Program&) = delete;
        Program(Program&&) = delete;
        Program& operator=(const Program&) = delete;
        Program& operator=(Program&&) = delete;

        void Init();

    private:
        static SoilSensorTask m_SoilSensorTask;
    };
}
#endif