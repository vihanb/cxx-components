#pragma once

#include <hap.h>

#include "homekit_types.hpp"
#include "homekit_accessory.hpp"
#include "homekit_service.hpp"
#include "homekit_characteristic.hpp"
#include "homekit_write_data.hpp"

namespace HomeKit {

class HomeKit {
    std::string _setupCode;
    std::string _setupId;
    std::vector<std::unique_ptr<Accessory>> accessories;

public:
    HomeKit(const char *setupCode, const char *setupId);
    virtual ~HomeKit();

    void init();
    void start();

    template <typename... Args>
    Accessory *addAccessory(Args&&... args) {
        accessories.push_back(std::make_unique<Accessory>(std::forward<Args>(args)...));
        return accessories.back().get();
    }

    void addAccessory(Accessory&& accessory) {
        accessories.push_back(std::make_unique<Accessory>(std::move(accessory)));
    }

    void printQRCode();

    bool isProbablyPaired() const;
};

}