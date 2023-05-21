#ifndef I2C_MAX17043_HPP
#define I2C_MAX17043_HPP

#include "i2c/Master.hpp"

namespace i2c {
namespace devices {

class MAX17043 {
private:
    Master &master_;
    bool isMAX17044_;

    static constexpr i2c::Address ADDRESS = 0b0110110;

    static constexpr i2c::RegEntry REG_VCELL_MSB = {.reg=0x2, .size=1};
    static constexpr i2c::RegEntry REG_VCELL_LSB = {.reg=0x3, .size=1};

    static constexpr i2c::RegEntry REG_SOC_MSB = {.reg=0x4, .size=1};
    static constexpr i2c::RegEntry REG_SOC_LSB = {.reg=0x5, .size=1};

    template<struct i2c::RegEntry>
    std::uint8_t readByte();

public:
    explicit MAX17043(Master &master, bool isMAX17044 = false);

    float cellVoltage();
    float stateOfCharge();
};

} // i2c
} // devices

#endif //I2C_MAX17043_HPP
