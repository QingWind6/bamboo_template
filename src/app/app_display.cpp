#include "app_display.h"

#include <Arduino.h>
#include "app_manager.h"
#include "simplelog.h"

namespace
{
constexpr uint32_t kFrameIntervalMs = 500; // Draw at 2 FPS by default
}

AppDisplay::AppDisplay() : AppBase("app_display")
{
}

void AppDisplay::onSetup()
{
    SimpleLog::info(getName(), "onSetup");
}

void AppDisplay::onResume()
{
    SimpleLog::info(getName(), "onResume");
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
    SimpleLog::info(getName(), "onPause");
}

void AppDisplay::onDestroy()
{
    SimpleLog::info(getName(), "onDestroy");
}

void AppDisplay::drawFrame()
{
    SimpleLog::info(getName(), "drawFrame");
}
