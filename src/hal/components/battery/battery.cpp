#include "battery.h"
#include "../../hal_config.h"
#include "simplelog.h"

#include "Arduino.h"

#define BATTERY_LOG "BatteryEsp32"

void BatteryEsp32::init()
{
    SimpleLog::info(BATTERY_LOG, "init");
    pinMode(HAL_ADC_EN, OUTPUT);
    analogReadResolution(12);
    analogSetPinAttenuation(HAL_BATTERY_PIN, ADC_11db);
}

bool BatteryEsp32::is_battery_inserted()
{
    const int MIN_VALID_VOLTAGE_MV = 500;
    const int SAMPLE_COUNT = 10;
    const int SAMPLE_INTERVAL_MS = 25;
    const int NO_BAT_THRESHOLD_MV = 300;
    return detect_battery_presence_by_ripple(
        SAMPLE_COUNT, SAMPLE_INTERVAL_MS, NO_BAT_THRESHOLD_MV, MIN_VALID_VOLTAGE_MV, "EE04");
}


float BatteryEsp32::readVoltage()
{
    if (!is_battery_inserted()) {
        return NO_BATTERY_DETECTED;
    }

    int avgMv = 0;
    if (!batteryadc_sample_avg_mv(avgMv)) {
        return NO_BATTERY_DETECTED;
    }

    float v_adc = avgMv / 1000.0f;
    float v_bat = v_adc * 2.0f;
    // Log.infoln("[BSP] Battery ADC avg: %d mV (v_adc=%.3f V, v_bat=%.3f V)", avgMv, v_adc, v_bat);
    return v_bat;
}

float BatteryEsp32::readPercentage()
{ 
    float v_bat = readVoltage();
    if (v_bat == NO_BATTERY_DETECTED) {
        return NO_BATTERY_DETECTED;
    }

    float socPct = voltageToPercentLookup(v_bat);
    if (socPct < 0.0f) socPct = 0.0f;
    if (socPct > 100.0f) socPct = 100.0f;

    // serial.printf("[BSP] Battery Voltage = %.3f V, SoC = %d %%\n", v_bat, (int)(socPct + 0.5f));

    return socPct;
}

BatteryStatus::BatteryStatus_t BatteryEsp32::getBatteryId()
{
    return BatteryStatus::None;
}

float BatteryEsp32::voltageToPercentLookup(float v_bat) {
    if (BATTERY_CURVE_SIZE == 0) {
        return 0.0f;
    }

    if (v_bat <= BATTERY_CURVE[0].voltage) {
        return BATTERY_CURVE[0].soc;
    }
    if (v_bat >= BATTERY_CURVE[BATTERY_CURVE_SIZE - 1].voltage) {
        return BATTERY_CURVE[BATTERY_CURVE_SIZE - 1].soc;
    }

    for (size_t i = 0; i < BATTERY_CURVE_SIZE - 1; ++i) {
        const auto &low = BATTERY_CURVE[i];
        const auto &high = BATTERY_CURVE[i + 1];
        if (v_bat >= low.voltage && v_bat <= high.voltage) {
            if (high.voltage == low.voltage) {
                return high.soc;
            }
            float ratio = (v_bat - low.voltage) / (high.voltage - low.voltage);
            return low.soc + ratio * (high.soc - low.soc);
        }
    }
    return BATTERY_CURVE[BATTERY_CURVE_SIZE - 1].soc;
}


bool BatteryEsp32::detect_battery_presence_by_ripple(int sampleCount,int intervalMs,int rippleThresholdMv,int minValidVoltageMv,const char *label) {
    BatterySampleStats stats;
    if (!batteryadc_collect_samples(sampleCount, intervalMs, stats)) {
        SimpleLog::log(LogLevel::ERROR, "[{}][BatteryDetect:{}] Failed to collect ADC samples", BATTERY_LOG, label);
        return false;
    }

    const int diffMv = stats.maxMv - stats.minMv;
    SimpleLog::log(LogLevel::DEBUG, "[{}][BatteryDetect:{}] Min: {} mV, Max: {} mV, Diff: {} mV", BATTERY_LOG, label, stats.minMv, stats.maxMv, diffMv);

    if (stats.maxMv < minValidVoltageMv) {
        SimpleLog::log(LogLevel::DEBUG, "[{}][BatteryDetect:{}] Voltage too low ({} mV)", BATTERY_LOG, label, stats.maxMv);
        return false;
    }

    if (diffMv > rippleThresholdMv) {
        SimpleLog::log(LogLevel::DEBUG, "[{}][BatteryDetect:{}] Ripple {} mV > {} mV -> no battery", BATTERY_LOG, label, diffMv, rippleThresholdMv);
        return false;
    }

    return true;
}


bool BatteryEsp32::batteryadc_collect_samples(int sampleCount, int intervalMs, BatterySampleStats &stats)
{
    digitalWrite(HAL_ADC_EN, HIGH);
    delay(5);

    stats.sumMv = 0;
    stats.minMv = INT_MAX;
    stats.maxMv = 0;
    stats.count = 0;

    for (int i = 0; i < sampleCount; ++i) {
        int currentMv = analogReadMilliVolts(HAL_BATTERY_PIN);
        stats.sumMv += currentMv;
        if (currentMv < stats.minMv) {
            stats.minMv = currentMv;
        }
        if (currentMv > stats.maxMv) {
            stats.maxMv = currentMv;
        }
        stats.count++;
        if (i + 1 < sampleCount) {
            delay(intervalMs);
        }
    }
    digitalWrite(HAL_ADC_EN, LOW);

    return stats.count == sampleCount;
}

bool BatteryEsp32::batteryadc_sample_avg_mv(int &avgMv) {
    const int NUM_SAMPLES = 10;
    const int DELAY_BETWEEN_SAMPLES_MS = 25;

    BatterySampleStats stats;
    if (!batteryadc_collect_samples(NUM_SAMPLES, DELAY_BETWEEN_SAMPLES_MS, stats)) {
        SimpleLog::error(BATTERY_LOG, "Failed to collect ADC samples for averaging");
        return false;
    }

    avgMv = stats.sumMv / NUM_SAMPLES;
    const int rangeMv = stats.maxMv - stats.minMv;

    SimpleLog::log(LogLevel::DEBUG, "[{}] [ADC Avg] Avg: {} mV, Min: {} mV, Max: {} mV, Range: {} mV", BATTERY_LOG, avgMv, stats.minMv, stats.maxMv, rangeMv);

    return true;
}
