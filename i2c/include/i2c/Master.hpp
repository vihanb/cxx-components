#ifndef I2C_MASTER_HPP
#define I2C_MASTER_HPP

#include <cstdint>
#include <array>
#include <vector>
#include "i2c.hpp"

#define I2C_MASTER_TIMEOUT_MS   1000

namespace i2c {

class Master final {
public:
    template<std::size_t Size> using Buffer = std::array<std::uint8_t, Size>;

    using Address = std::uint8_t;
    using Register = std::uint8_t;

    explicit Master(i2c_config_t config);
    ~Master();

    Master(const Master &) = delete;
    Master(Master &&) = delete;

    template<std::size_t N>
    Buffer<N> readFromDevice(Address deviceAddress) {
        Buffer<N> response;
        ESP_ERROR_CHECK_WITHOUT_ABORT(
                i2c_master_read_from_device(_Port::MASTER, deviceAddress,
                                            response.data(), response.size(),
                                            I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS));
        return response;
    }

    template<std::size_t N, std::size_t M>
    Buffer<N> readWriteFromDevice(Address deviceAddress, Buffer<M> writeData) {
        Buffer<N> response;
        ESP_ERROR_CHECK_WITHOUT_ABORT(
                i2c_master_write_read_device(_Port::MASTER, deviceAddress,
                                             writeData.data(), writeData.size(),
                                             response.data(), response.size(),
                                             I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS));
        return response;
    }

    template<std::size_t N>
    Buffer<N> readFromDeviceAtRegister(Address deviceAddress, Register reg) {
        return readWriteFromDevice<N, 1>(deviceAddress, {reg});
    }

    template<RegEntry entry>
    Buffer<entry.size> readFromDeviceAtEntry(Address deviceAddress) {
        return readFromDeviceAtRegister<entry.size>(deviceAddress, entry.reg);
    }


    template<std::size_t N>
    esp_err_t writeToDevice(Address deviceAddress, Buffer<N> writeData) {
        esp_err_t res = i2c_master_write_to_device(_Port::MASTER, deviceAddress,
                                                   writeData.data(), writeData.size(),
                                                   I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);

        ESP_ERROR_CHECK_WITHOUT_ABORT(res);
        return res;
    }

    /**
     * Scans for responding I2C devices.
     * @return Sorted list of device addresses.
     */
    std::vector<uint8_t> scan();
};

}

#endif //I2C_MASTER_HPP
