#include "epaper.h"
#include "../../hal_config.h"
#include "simplelog.h"

#include <Arduino.h>

static constexpr const char* LOG_TAG = "EpaperEsp32";

void EpaperEsp32::init()
{
    if (initialized_) {
        return;
    }

    SimpleLog::info(LOG_TAG, "init");
    pinMode(HAL_EPD_ENABLE, OUTPUT);
    digitalWrite(HAL_EPD_ENABLE, HIGH);

    _epaper.begin();
    _epaper.fillScreen(TFT_WHITE);
    _epaper.update();

    initialized_ = true;
}

void EpaperEsp32::clear()
{
    if (!initialized_) {
        init();
    }
    _epaper.fillScreen(TFT_WHITE);
    _epaper.update();
}

EPaper* EpaperEsp32::Get()
{
    return &_epaper;
}
