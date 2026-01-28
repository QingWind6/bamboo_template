#pragma once

#include "bambooloop.h"

class AppDisplay : public AppBase {
public:
    AppDisplay();
    ~AppDisplay() override = default;

    void onSetup() override;
    void onRunning() override;
    void onDestroy() override;
    std::string getName() const { return _app_name; }

private:
    std::string _app_name;
};