#pragma once

#include "hal.h"

#include "TFT_eSPI.h"

class EpaperEsp32 : public hal_components::EpaperBase{
public:
    void init() override;
    void clear() override;

    EPaper* Get() override;

private:
    EPaper _epaper;
    bool initialized_ = false;
};
