#pragma once

#include <memory>

#include "components/battery.h"
#include "components/button.h"
#include "components/epaper.h"
#include "components/indicator.h"


namespace HAL{

class HalBase{
public:
    HalBase();
    virtual ~HalBase() = default;

    // Initialize the HAL and any registered components.
    virtual void init();

    hal_components::BatteryBase& GetBattery();
    hal_components::ButtonBase& GetButton();
    hal_components::EpaperBase& GetEpaper();
    hal_components::IndicatorBase& GetIndicator();
};

HalBase& Get();

}
