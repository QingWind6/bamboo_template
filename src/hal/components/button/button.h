#pragma once

#include "hal.h"

class ButtonEsp32 : public hal_components::ButtonBase {
public: 
    void init() override;
    void update() override;

    ButtonEvent::ButtonEvent_t get_event(ButtonId::ButtonId_t button_id) override;

private:
    ButtonEvent::ButtonEvent_t button1_event_ = ButtonEvent::None;
    ButtonEvent::ButtonEvent_t button2_event_ = ButtonEvent::None;
    ButtonEvent::ButtonEvent_t button3_event_ = ButtonEvent::None;

    friend void _button1_click();
    friend void _button2_click();
    friend void _button3_click();
    friend void _button1_longpress();
    friend void _button2_longpress();
    friend void _button3_longpress();
    void set_event(ButtonId::ButtonId_t button_id, ButtonEvent::ButtonEvent_t event);
};
