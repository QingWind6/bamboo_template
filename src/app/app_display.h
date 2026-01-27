#pragma once

#include <cstdint>

#include "app_base.h"

class AppDisplay : public AppBase
{
public:
    AppDisplay();
    ~AppDisplay() override = default;

    void onSetup() override;
    void onResume() override;
    void onRunning() override;
    void onPause() override;
    void onDestroy() override;

private:
    uint32_t _last_draw_ms = 0;

    void drawFrame();
};
