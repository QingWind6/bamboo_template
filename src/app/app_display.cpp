#include "app_display.h"

#include <Arduino.h>
#include "app_manager.h"
#include "simplelog.h"

namespace
{
constexpr uint32_t kFrameIntervalMs = 500; // Draw at 2 FPS by default
}

AppDisplay::AppDisplay() : AppBase("display_app")
{
}

void AppDisplay::onSetup()
{
    SimpleLog::info("[AppDisplay] setup");
}

void AppDisplay::onResume()
{
    SimpleLog::info("[AppDisplay] resume");
    _last_draw_ms = millis();
}

void AppDisplay::onRunning()
{
    const uint32_t now = millis();
    if (now - _last_draw_ms < kFrameIntervalMs)
    {
        return;
    }

    drawFrame();
    _last_draw_ms = now;
}

void AppDisplay::onPause()
{
    SimpleLog::info("[AppDisplay] pause");
}

void AppDisplay::onDestroy()
{
    SimpleLog::info("[AppDisplay] destroy");
}

void AppDisplay::drawFrame()
{
    SimpleLog::info("[AppDisplay] drawing frame");
}
