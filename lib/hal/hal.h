#pragma once

#include <memory>
#include <string>

#include "components/battery.h"
#include "components/button.h"
#include "components/epaper.h"
#include "components/indicator.h"


namespace HAL{

class HalBase{
public:
    HalBase();
    virtual ~HalBase();
    // 返回当前 HAL 实现的类型名称，用于日志调试
    virtual std::string type() { return "HalBase"; }

    // 初始化 HAL 及其注册的组件
    virtual void init();

    hal_components::BatteryBase& GetBattery();
    hal_components::ButtonBase& GetButton();
    hal_components::EpaperBase& GetEpaper();
    hal_components::IndicatorBase& GetIndicator();
protected:
    // 组件指针，由派生类在 init() 中赋值
    // 使用 unique_ptr 管理生命周期
    std::unique_ptr<hal_components::BatteryBase> battery_;
    std::unique_ptr<hal_components::ButtonBase> button_;
    std::unique_ptr<hal_components::EpaperBase> epaper_;
    std::unique_ptr<hal_components::IndicatorBase> indicator_;
};

// --- 全局入口 ---

// 1. 获取全局 HAL 实例 (如果未注入，自动创建默认基类)
HalBase& Get();

// 2. 注入 HAL 实例
void Inject(std::unique_ptr<HalBase> hal);

// 3.销毁全局 HAL 实例
void Destroy();

}
