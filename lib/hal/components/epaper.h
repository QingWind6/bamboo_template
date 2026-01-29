#pragma once

namespace hal_components {

class EpaperBase{
public:
    virtual ~EpaperBase() = default;

    virtual void init(){}
    virtual void clear(){}
    // virtual void displayImage(const unsigned char* imageData){};
};
}
