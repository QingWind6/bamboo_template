#include "app_device_info.h"
#include "simplelog.h"
#include <Arduino.h>

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

    SimpleLog::info(getName(), "running");
}

void AppDeviceInfo::onDestroy() {
    SimpleLog::info(getName(), "destroy");
}