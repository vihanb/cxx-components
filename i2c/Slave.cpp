#include "i2c/Slave.hpp"
#include <mutex>

namespace i2c {

static std::mutex _slaveLock;

Slave::Slave(i2c_config_t config, std::size_t rxBufferSize, std::size_t txBufferSize) {
    if (!_slaveLock.try_lock()) {
        throw std::runtime_error("I2C Slave already allocated.");
    }

    i2c_param_config(_Port::SLAVE, &config);
    ESP_ERROR_CHECK(i2c_driver_install(_Port::SLAVE, I2C_MODE_SLAVE,
                                       rxBufferSize, txBufferSize, 0));
}

Slave::~Slave() {
    i2c_driver_delete(_Port::SLAVE);
    _slaveLock.unlock();
}

}