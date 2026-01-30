#include <Arduino.h>

#include "utils/utils.h"
#include "simplelog.h"

#include "app/app_device_info.h"
#include "app/app_display.h"

#include "hal/hal_esp32.h"

SemaphoreHandle_t logMutex;
Scheduler bambooloop;


void setup_logging() {
    logMutex = xSemaphoreCreateMutex();

    SimpleLog::setLock(
        []() { xSemaphoreTake(logMutex, portMAX_DELAY); },
        []() { xSemaphoreGive(logMutex); }
    );

    // 3. 注入输出和时间
    SimpleLog::setOutput([](std::string_view msg){
        printf("%.*s", static_cast<int>(msg.size()), msg.data());
    });
    SimpleLog::setTime([](){ return (uint32_t)esp_timer_get_time() / 1000; }); // 微秒转毫秒
    SimpleLog::setLevelTagEnabled(false);

}

void setup()
{
    vTaskDelay(3000);
    setup_logging();

    SimpleLog::info("Hello, world!");

    bambooloop.install<AppDeviceInfo>();
    bambooloop.install<AppDisplay>();

    HAL::Inject(std::make_unique<HalEsp32>());
    float voltage = HAL::Get().GetBattery().readVoltage();
}

void loop()
{
    bambooloop.update();
    vTaskDelay(10);
}
