#pragma once

#include "hal.h"

class HalEsp32 : public HAL::HalBase {
public:
    std::string type() override
    {
        return "HalEsp32";
    }

    void init() override;

private:
    void hal_test();

};