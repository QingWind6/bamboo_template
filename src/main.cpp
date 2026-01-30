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

    // inject output and time functions
    SimpleLog::setOutput([](std::string_view msg){
        printf("%.*s", static_cast<int>(msg.size()), msg.data());
    });
    SimpleLog::setTime([](){ return (uint32_t)esp_timer_get_time() / 1000; }); // us2ms
    SimpleLog::setLevelTagEnabled(false);

}

void setup()
{
    delay(2000);
    setup_logging();
    SimpleLog::info("Hello World!");

    HAL::Inject(std::make_unique<HalEsp32>());
    bambooloop.install<AppDeviceInfo>();
    bambooloop.install<AppDisplay>();
}

void loop()
{
    HAL::Get().update();
    bambooloop.update();
    vTaskDelay(10);
}
