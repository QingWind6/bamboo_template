#include "app_device_info.h"

#include "simplelog.h"

AppDeviceInfo::AppDeviceInfo() : AppBase("DeviceInfo") {}

void AppDeviceInfo::onSetup()
{ 
    SimpleLog::info(getName(), "onSetup");
}