#pragma once

namespace BatteryStatus{
enum BatteryStatus_t{
    None = 0, 
    Low, 
    Normal, 
    Charging
};
}

namespace hal_components {

class BatteryBase{
public:
    virtual ~BatteryBase() = default;

    virtual void init(){};
    virtual float readVoltage(){ return 0.0f; }
    virtual float readPercentage(){ return 0.0f; }

    virtual BatteryStatus::BatteryStatus_t getBatteryId(){ return BatteryStatus::None; }
};
}
