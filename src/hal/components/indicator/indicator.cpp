#include "indicator.h"
#include "../../hal_config.h"
#include "Arduino.h"
#include "simplelog.h"

void IndicatorEsp32::init()
{
    pinMode(HAL_GREENLED_PIN, OUTPUT);
}

void IndicatorEsp32::setIndicator(bool on)
{
    digitalWrite(HAL_GREENLED_PIN, on);
}