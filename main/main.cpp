#include <iostream>

#include "sdkconfig.h"
#include "Program.h"


extern "C" void app_main(void)
{
    const gg::Program program{};
    program.Init();
}
