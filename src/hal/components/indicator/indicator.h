#pragma once

#include "hal.h"

class IndicatorEsp32 : public hal_components::IndicatorBase{
public:
    IndicatorEsp32(){}

    void init() override;

    void setIndicator(bool on) override;
};