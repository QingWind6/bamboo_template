#pragma once

#include "hal.h"
#include <limits.h>

struct BatteryCurvePoint
{
    float soc;
    float voltage;
};

static const BatteryCurvePoint BATTERY_CURVE[] = {
    {0.0f, 2.910f},
    {2.0f, 3.060f},
    {3.0f, 3.150f},
    {4.0f, 3.220f},
    {5.0f, 3.280f},
    {6.0f, 3.320f},
    {7.0f, 3.360f},
    {8.0f, 3.390f},
    {9.0f, 3.420f},
    {10.0f, 3.450f},
    {12.0f, 3.500f},
    {14.0f, 3.540f},
    {16.0f, 3.570f},
    {18.0f, 3.600f},
    {20.0f, 3.630f},
    {25.0f, 3.690f},
    {30.0f, 3.740f},
    {35.0f, 3.790f},
    {40.0f, 3.830f},
    {45.0f, 3.870f},
    {50.0f, 3.910f},
    {55.0f, 3.940f},
    {60.0f, 3.980f},
    {65.0f, 4.010f},
    {70.0f, 4.040f},
    {75.0f, 4.070f},
    {80.0f, 4.090f},
    {85.0f, 4.120f},
    {90.0f, 4.140f},
    {100.0f, 4.150f},
};

class BatteryEsp32 : public hal_components::BatteryBase {

public:
    void init() override;
    float readVoltage() override;
    float readPercentage() override;
    bool is_battery_inserted();

    BatteryStatus::BatteryStatus_t getBatteryId() override;

private:
struct BatterySampleStats {
    long sumMv = 0;
    int minMv = INT_MAX;
    int maxMv = 0;
    int count = 0;
};

    const size_t BATTERY_CURVE_SIZE = sizeof(BATTERY_CURVE) / sizeof(BATTERY_CURVE[0]);
    const float NO_BATTERY_DETECTED = -1.0f;
    const float LOW_BATTERY_PERCENT_THRESHOLD = 5.0f;

    bool batteryadc_sample_avg_mv(int &avg_mv);
    float voltageToPercentLookup(float v_bat);
    bool detect_battery_presence_by_ripple(int sampleCount, int intervalMs, int rippleThresholdMv, int minValidVoltageMv, const char *label);
    bool batteryadc_collect_samples(int sampleCount, int intervalMs, BatterySampleStats &stats);
};