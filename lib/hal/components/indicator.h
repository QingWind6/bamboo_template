#pragma once

namespace hal_components {

class IndicatorBase {
public:
    virtual ~IndicatorBase() = default;

    virtual void init(){}
    virtual void setIndicator(bool on){}
};
}
