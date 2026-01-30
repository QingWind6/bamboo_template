#include "app_display.h"

#include <Arduino.h>
#include "simplelog.h"

#include "hal/hal_esp32.h"

AppDisplay::AppDisplay() { _app_name = "AppDisplay"; }


void AppDisplay::onSetup() {
    SimpleLog::info(getName(), "setup");
}

void AppDisplay::onRunning() {
    SimpleLog::info(getName(), "running");
    static ButtonEvent::ButtonEvent_t button_id = ButtonEvent::None;
    HAL::Get().GetButton().update();
    button_id = HAL::Get().GetButton().get_event(ButtonId::ButtonId_t::KEY0);
    if(button_id == ButtonEvent::click)
    {
        SimpleLog::info(getName(), "Button KEY0 clicked, clearing display");
        HAL::Get().GetEpaper().clear();
    }
}

void AppDisplay::onDestroy() {
    SimpleLog::info(getName(), "destroy");
}

