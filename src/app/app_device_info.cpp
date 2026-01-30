#include "app_device_info.h"
#include "simplelog.h"
#include <Arduino.h>

#include "hal/hal_esp32.h"

AppDeviceInfo::AppDeviceInfo() { _app_name = "AppDeviceInfo"; }

void AppDeviceInfo::onSetup() {
    SimpleLog::info(getName(), "setup");
    _last_update_ms = millis();
}

void AppDeviceInfo::onRunning() {
    const uint32_t now = millis();
    if (now - _last_update_ms < 1000) {
        return; // 每 1s 触发一次
    }
    _last_update_ms = now;

    // SimpleLog::info(getName(), "running");
    float voltage = HAL::Get().GetBattery().readVoltage();
    SimpleLog::log(LogLevel::INFO, "Battery voltage: {:.2f} V", voltage);
}

void AppDeviceInfo::onDestroy() {
    SimpleLog::info(getName(), "destroy");
}