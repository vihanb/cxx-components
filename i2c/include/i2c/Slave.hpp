#ifndef I2C_SLAVE_HPP
#define I2C_SLAVE_HPP

#include <driver/i2c.h>
#include <Task.hpp>
#include <vector>
#include <unordered_map>
#include "i2c.hpp"

namespace i2c {

class Slave {
public:
    Slave(i2c_config_t config, std::size_t rxBufferSize, std::size_t txBufferSize);
    virtual ~Slave();

    Slave(const Slave &) = delete;
    Slave(Slave &&) = delete;
};

}

#endif //I2C_SLAVE_HPP
