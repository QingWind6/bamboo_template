#include "hal.h"

#include <memory>
#include <utility>

#include "simplelog.h"

#define LOG_TAG "HAL"

using namespace HAL;

static std::unique_ptr<HalBase> g_hal = nullptr;

HalBase::HalBase()
{
}

HalBase::~HalBase()
{
    SimpleLog::info(LOG_TAG, "HAL Destroyed");
}

// void HalBase::init()
// {
//     SimpleLog::log(LOG_TAG, "HalBase init");
// }

hal_components::BatteryBase& HalBase::GetBattery()
{
    if(!battery_)
    {
        SimpleLog::warn(LOG_TAG, "get battery null");
        battery_ = std::make_unique<hal_components::BatteryBase>();
    }
    return *battery_;
}

hal_components::ButtonBase& HalBase::GetButton()
{
    if(!button_)
    {
        SimpleLog::warn(LOG_TAG, "get button null");
        button_ = std::make_unique<hal_components::ButtonBase>();
    }
    return *button_;
}

hal_components::EpaperBase& HalBase::GetEpaper()
{
    if(!epaper_)
    {
        SimpleLog::warn(LOG_TAG, "get epaper null");
        epaper_ = std::make_unique<hal_components::EpaperBase>();
    }
    return *epaper_;
}

hal_components::IndicatorBase& HalBase::GetIndicator()
{
    if(!indicator_)
    {
        SimpleLog::warn(LOG_TAG, "get indicator null");
        indicator_ = std::make_unique<hal_components::IndicatorBase>();
    }
    return *indicator_;
}

void Inject(std::unique_ptr<HalBase> hal)
{
    if(hal)
    {
        Destroy();
        g_hal = std::move(hal);
        SimpleLog::log(LOG_TAG, "Inject HAL: %s", g_hal->type().c_str());
        g_hal->init();
    }else
    {
        SimpleLog::warn(LOG_TAG, "Attempt to inject nullptr HAL !!");
    }
}

HalBase& Get()
{
    if(!g_hal)
    {
        SimpleLog::warn(LOG_TAG, "get HAL null");
        Inject(std::make_unique<HalBase>());
    }
    return *g_hal;
}

void Destroy()
{
    if(g_hal)
    {
        SimpleLog::log(LOG_TAG, "Destroy HAL: %s", g_hal->type().c_str());
        g_hal.reset();
    }
}
