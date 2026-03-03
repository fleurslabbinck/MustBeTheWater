#include <iostream>

#include "sdkconfig.h"
#include "Application.h"

extern "C" void app_main(void)
{
    const gg::Application app{};
    app.Init();
}