#include <iostream>

#include "sdkconfig.h"
#include "Program.h"

static gg::Program program{};

extern "C" void app_main(void)
{
    program.Init();
}
