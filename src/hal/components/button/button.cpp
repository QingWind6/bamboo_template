#include "button.h"
#include "../../hal_config.h"
#include "simplelog.h"

#include "OneButton.h"

OneButton button1(HAL_KEY0_PIN, true);
OneButton button2(HAL_KEY1_PIN, true);
OneButton button3(HAL_KEY2_PIN, true);

static ButtonEsp32* g_button = nullptr;

void _button1_click()
{
    if(g_button)
    {
        g_button->set_event(ButtonId::KEY0, ButtonEvent::click);
    }
}

void _button2_click()
{
    if(g_button)
    {
        g_button->set_event(ButtonId::KEY1, ButtonEvent::click);
    }
}

void _button3_click()
{
    if(g_button)
    {
        g_button->set_event(ButtonId::KEY2, ButtonEvent::click);
    }
}

void ButtonEsp32::init()
{
    SimpleLog::info("ButtonEsp32", "init");
    g_button = this;
    button1.attachClick(_button1_click);
    button2.attachClick(_button2_click);
    button3.attachClick(_button3_click);
}

void ButtonEsp32::update()
{
    button1.tick();
    button2.tick();
    button3.tick();
}

void ButtonEsp32::set_event(ButtonId::ButtonId_t button_id, ButtonEvent::ButtonEvent_t event)
{
    switch(button_id)
    {
        case ButtonId::KEY0: button1_event_ = event; break;
        case ButtonId::KEY1: button2_event_ = event; break;
        case ButtonId::KEY2: button3_event_ = event; break;
        default: break;
    }
}

ButtonEvent::ButtonEvent_t ButtonEsp32::get_event(ButtonId::ButtonId_t button_id)
{
    // Return the current event and clear it so it is edge-triggered.
    switch(button_id)
    {
        case ButtonId::KEY0:
        {
            auto evt = button1_event_;
            button1_event_ = ButtonEvent::None;
            return evt;
        }
        case ButtonId::KEY1:
        {
            auto evt = button2_event_;
            button2_event_ = ButtonEvent::None;
            return evt;
        }
        case ButtonId::KEY2:
        {
            auto evt = button3_event_;
            button3_event_ = ButtonEvent::None;
            return evt;
        }
        default:
            return ButtonEvent::None;
    }
}
