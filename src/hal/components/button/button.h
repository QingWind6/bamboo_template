#pragma once

#include "hal.h"

class ButtonEsp32 : public hal_components::ButtonBase {
public: 
    void init() override;
    void update() override;

    void set_event(ButtonId::ButtonId_t button_id, ButtonEvent::ButtonEvent_t event);
    ButtonEvent::ButtonEvent_t get_event(ButtonId::ButtonId_t button_id);

private:
    ButtonEvent::ButtonEvent_t button1_event_ = ButtonEvent::None;
    ButtonEvent::ButtonEvent_t button2_event_ = ButtonEvent::None;
    ButtonEvent::ButtonEvent_t button3_event_ = ButtonEvent::None;
};

