#pragma once

// 定义温湿度数据结构体
struct EnvData_t {
    float temperature;
    float humidity;
    uint32_t timestamp; // 可选：记录更新时间
};

// 约定 Key 名称
#define KEY_ENV_DATA "env_data"