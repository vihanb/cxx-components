#include "i2c/Master.hpp"
#include <mutex>
namespace i2c {

static std::mutex _masterLock;

Master::Master(i2c_config_t config) {
    if (!_masterLock.try_lock()) {
        throw std::runtime_error("I2C Master already allocated.");
    }

    i2c_param_config(_Port::MASTER, &config);
    ESP_ERROR_CHECK(i2c_driver_install(_Port::MASTER, I2C_MODE_MASTER, 0, 0, 0));
}

Master::~Master() {
    i2c_driver_delete(_Port::MASTER);
    _masterLock.unlock();
}

std::vector<std::uint8_t> Master::scan() {
    std::vector<std::uint8_t> addresses;

    for (int i = 1; i < 127; i++) {
        if (writeToDevice<1>(i, {1}) == ESP_OK) {
            addresses.push_back(i);
        }
    }

    return addresses;
}

}