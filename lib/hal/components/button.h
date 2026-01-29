#pragma once

namespace ButtonId{
enum ButtonId_t{
    None = 0, 
    KEY0, 
    KEY1,
    KEY2
};
}

namespace hal_components {

class ButtonBase {
public:
    virtual ~ButtonBase() = default;

    virtual void init(){}
    virtual void update(){}
};


}
