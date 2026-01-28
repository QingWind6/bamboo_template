#include "app_display.h"

#include <Arduino.h>
#include "simplelog.h"

AppDisplay::AppDisplay() { _app_name = "AppDisplay"; }


void AppDisplay::onSetup() {
    SimpleLog::info(getName(), "setup");
}

void AppDisplay::onRunning() {
    SimpleLog::info(getName(), "running");
}

void AppDisplay::onDestroy() {
    SimpleLog::info(getName(), "destroy");
}

