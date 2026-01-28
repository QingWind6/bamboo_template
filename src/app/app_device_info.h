#pragma once

#include "bambooloop.h"

class AppDeviceInfo : public AppBase {
public:
    AppDeviceInfo();
    ~AppDeviceInfo() override = default;

    void onSetup() override;
    void onRunning() override;
    void onDestroy() override;

    std::string getName() const { return _app_name; }

private:
    std::string _app_name;
    uint32_t _last_update_ms = 0;
};
