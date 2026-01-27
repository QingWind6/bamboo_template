#include "utils.h"
#include "Arduino.h"
#include "simplelog.h"

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
    SimpleLog::info("Memory Status:");
    SimpleLog::info("    {:<12}  /  {:<12}  /  {:<12}  /  {:<12}", "Max Alloc", "Used", "Free", "Total");
    SimpleLog::info("  DRAM:");
    SimpleLog::info("    [{:>10} B /{:>10} B /{:>10} B /{:>10} B]", heapMaxBlock, heapUsed, heapFree, heapTotal);

    // If PSRAM is available, print PSRAM stats
    if (psramTotal > 0)
    {
        SimpleLog::info("  PSRAM:");
        SimpleLog::info("    [{:>10} B /{:>10} B /{:>10} B /{:>10} B]", psramMaxBlock, psramUsed, psramFree, psramTotal);
    }
    else
    {
        SimpleLog::info("  PSRAM: Unavailable");
    }

    SimpleLog::info("");
}
