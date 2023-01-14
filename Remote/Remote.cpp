#include "Remote.hpp"

namespace Remote {

Channel::Channel(gpio_num_t gpio) : _channel(RMT_CHANNEL_0) {
    rmt_config_t config = RMT_DEFAULT_CONFIG_TX(gpio, _channel);
    config.tx_config.carrier_en = true;
    ESP_ERROR_CHECK(rmt_config(&config));
    ESP_ERROR_CHECK(rmt_driver_install(_channel, 0, 0));

    uint32_t clockHz;
    rmt_get_counter_clock(_channel, &clockHz);
    _clockMHz = (float)clockHz / 1e6;
}

Channel::~Channel() {
    ESP_ERROR_CHECK(rmt_driver_uninstall(_channel));
}

void Channel::execute(rmt_item32_t *commandData, std::size_t commandSize) {
    rmt_write_items(_channel, commandData, commandSize, true);
}

}
