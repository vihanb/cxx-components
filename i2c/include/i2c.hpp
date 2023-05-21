#pragma once

#include <driver/i2c.h>
#include <cstdint>


namespace i2c {

namespace _Port {
static std::uint8_t MASTER = 0;
static std::uint8_t SLAVE = 1;
}

using Address = std::uint8_t;
using Register = std::uint8_t;

struct RegEntry {
    const Register reg;
    const std::size_t size;
};

}