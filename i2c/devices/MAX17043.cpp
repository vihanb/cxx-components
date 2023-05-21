#include "MAX17043.hpp"
#include <cmath>

namespace i2c {
namespace devices {

MAX17043::MAX17043(Master &master, bool isMAX17044) : master_(master), isMAX17044_(isMAX17044) {}

template<i2c::RegEntry entry>
std::uint8_t MAX17043::readByte() {
    return master_.readFromDeviceAtEntry<entry>(ADDRESS)[0];
}

float MAX17043::cellVoltage() {
    std::uint32_t msb = readByte<REG_VCELL_MSB>();
    std::uint32_t lsb = readByte<REG_VCELL_LSB>();

    std::uint32_t vcell = (lsb >> 4) + (msb << 4);

    if (isMAX17044_) {
        return vcell * 0.00250;
    } else {
        return vcell * 0.00125;
    }
}

float MAX17043::stateOfCharge() {
    float msb = readByte<REG_SOC_MSB>();
    float lsb = readByte<REG_SOC_LSB>();

    return msb + (lsb / pow(2, 8));
}

} // i2c
} // devices
