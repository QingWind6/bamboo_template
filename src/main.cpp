#include <Arduino.h>

void printMemoryStatus()
{
    // -- DRAM (Internal Heap) status -- //
    size_t heapTotal = ESP.getHeapSize();        // Total heap area size (bytes)
    size_t heapFree = ESP.getFreeHeap();         // Free heap size (bytes)
    size_t heapMaxBlock = ESP.getMaxAllocHeap(); // Largest single allocatable heap block (bytes)
    size_t heapUsed = heapTotal - heapFree;      // Used heap size (bytes)

    // -- PSRAM section (if available) -- //
    size_t psramTotal = ESP.getPsramSize(); // Total external PSRAM size (bytes), 0 if unsupported
    size_t psramFree = 0;
    size_t psramMaxBlock = 0;
    size_t psramUsed = 0;
    if (psramTotal > 0)
    {
        psramFree = ESP.getFreePsram();         // Free PSRAM size (bytes)
        psramMaxBlock = ESP.getMaxAllocPsram(); // Largest single allocatable PSRAM block (bytes)
        psramUsed = psramTotal - psramFree;     // Used PSRAM size (bytes)
    }

    // Print header
    Serial.println("Memory Status:");
    Serial.printf("    %-12s  /  %-12s  /  %-12s  /  %-12s\n", "Max Alloc", "Used", "Free", "Total");
    Serial.println("  DRAM:");
    Serial.printf("    [%10u B /%10u B /%10u B /%10u B]\n", heapMaxBlock, heapUsed, heapFree, heapTotal);

    // If PSRAM is available, print PSRAM stats
    if (psramTotal > 0)
    {
        Serial.println("  PSRAM:");
        Serial.printf("    [%10u B /%10u B /%10u B /%10u B]\n", psramMaxBlock, psramUsed, psramFree, psramTotal);
    }
    else
    {
        Serial.println("  PSRAM: Unavailable");
    }

    Serial.println();
}

void __app_device_info_task(void *pvParameters)
{
    while (1)
    {
        Serial.println("[BSP] Device info:");
        vTaskDelay(2000);
    }
    vTaskDelete(NULL);
}

void _app_info_printer_task(void *pvParameters)
{
    while (1)
    {
        printMemoryStatus();
        vTaskDelay(5000);
    }
    vTaskDelete(NULL);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Hello, world!");

    xTaskCreatePinnedToCore(__app_device_info_task, "app_device_info", 4096, NULL, 5, NULL, 0);

    xTaskCreatePinnedToCore(_app_info_printer_task, "app_info_printer", 4096, NULL, 5, NULL, 0);
}

void loop()
{
    Serial.println("Hello, Bamboo!");
    delay(1000);
}
