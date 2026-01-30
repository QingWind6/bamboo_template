#include "app_display.h"

#include <Arduino.h>
#include "simplelog.h"

#include "hal/hal_esp32.h"

#include "TFT_eSPI.h"

AppDisplay::AppDisplay() { _app_name = "AppDisplay"; }


void AppDisplay::onSetup() {
    SimpleLog::info(getName(), "setup");
}

void AppDisplay::onRunning() {
    // SimpleLog::info(getName(), "running");
    static ButtonEvent::ButtonEvent_t button0_id = ButtonEvent::None;
    static ButtonEvent::ButtonEvent_t button1_id = ButtonEvent::None;
    static ButtonEvent::ButtonEvent_t button2_id = ButtonEvent::None;
    // button0_id = HAL::Get().GetButton().get_event(ButtonId::ButtonId_t::KEY0);
    // button1_id = HAL::Get().GetButton().get_event(ButtonId::ButtonId_t::KEY1);
    // button2_id = HAL::Get().GetButton().get_event(ButtonId::ButtonId_t::KEY2);
    // if(button0_id == ButtonEvent::click)
    // {
    //     SimpleLog::info(getName(), "Button KEY0 clicked, clearing display");
    //     HAL::Get().GetIndicator().setIndicator(false);
    //     HAL::Get().GetEpaper().clear();
    // }else if(button1_id == ButtonEvent::click)
    // {
    //     SimpleLog::info(getName(), "Button KEY1 clicked, displaying black screen");
    //     HAL::Get().GetIndicator().setIndicator(true);
    //     HAL::Get().GetEpaper().Get()->fillScreen(TFT_BLACK);
    //     HAL::Get().GetEpaper().Get()->update();
    // }
    static bool key0_lp = false, key1_lp = false;
    auto e0 = HAL::Get().GetButton().get_event(ButtonId::KEY0);
    auto e1 = HAL::Get().GetButton().get_event(ButtonId::KEY1);

    if (e0 == ButtonEvent::longpress) key0_lp = true;
    if (e1 == ButtonEvent::longpress) key1_lp = true;

    if (key0_lp && key1_lp) {
        SimpleLog::info(getName(), "KEY0+KEY1 longpress");
        key0_lp = key1_lp = false;  // 处理完再清掉
    }
}

void AppDisplay::onDestroy() {
    SimpleLog::info(getName(), "destroy");
}

