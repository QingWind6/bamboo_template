#pragma once

namespace ButtonId{
enum ButtonId_t{
    None = 0, 
    KEY0, 
    KEY1,
    KEY2
};
}

namespace ButtonEvent{
enum ButtonEvent_t{
    None = 0, 
    click,
    longpress
};
}

namespace hal_components {

class ButtonBase {
public:
    virtual ~ButtonBase() = default;

    virtual void init(){}
    virtual void update(){}
    virtual ButtonEvent::ButtonEvent_t get_event(ButtonId::ButtonId_t){ return ButtonEvent::None; }
};


}
