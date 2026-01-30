#pragma once

class EPaper;

namespace hal_components {

class EpaperBase{
public:
    virtual ~EpaperBase() = default;

    virtual void init(){}
    virtual void clear(){}
    virtual EPaper* Get(){ return nullptr; }
    // virtual void displayImage(const unsigned char* imageData){};
};
}
