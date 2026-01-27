#pragma once

#include "app_manager.h"

class AppDeviceInfo : public AppBase {
public:
    AppDeviceInfo();
    ~AppDeviceInfo() override = default;

    void onSetup() override;
    void onRunning() override;
    void onPause() override;
    void onResume() override;
    void onDestroy() override;

private:
    
};
