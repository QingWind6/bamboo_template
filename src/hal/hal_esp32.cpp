#include "hal_esp32.h"
#include "hal_config.h"

#include "components/button/button.h"
#include "components/indicator/indicator.h"
#include "components/battery/battery.h"
#include "components/epaper/epaper.h"

// #include ""

void HalEsp32::init()
{
    button_ = std::make_unique<ButtonEsp32>();
    button_->init();

    battery_ = std::make_unique<BatteryEsp32>();
    battery_->init();

    epaper_ = std::make_unique<EpaperEsp32>();
    epaper_->init();
}

void HalEsp32::hal_test()
{

}
