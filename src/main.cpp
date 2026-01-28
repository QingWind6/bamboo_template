#include <Arduino.h>

#include "app/app_display.h"
#include "app_manager.h"
#include "utils/utils.h"

#include "simplelog.h"

SemaphoreHandle_t logMutex;
static AppManager g_app_manager;

void __app_device_info_task(void *pvParameters)
{
    while (1)
    {
        SimpleLog::warn("BSP", "Device info:");
        vTaskDelay(2000);
    }
    vTaskDelete(NULL);
}

void __app_info_printer_task(void *pvParameters)
{
    while (1)
    {
        printMemoryStatus();
        vTaskDelay(5000);
    }
    vTaskDelete(NULL);
}

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
}

void setup()
{
    // Serial.begin(115200);
    vTaskDelay(3000);
    setup_logging();

    SimpleLog::info("Hello, world!");

    auto *display_app = new AppDisplay();
    g_app_manager.startApp(display_app);

    xTaskCreatePinnedToCore(__app_device_info_task, "app_device_info", 4096, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(__app_info_printer_task, "app_info_printer", 4096, NULL, 5, NULL, 0);
}

void loop()
{
    g_app_manager.update();
    vTaskDelay(20);
}
