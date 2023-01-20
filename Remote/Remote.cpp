#include "Remote.hpp"

namespace Remote {

static std::mutex _channelLock;
static uint32_t _channelSlots = 0b1111;

rmt_channel_t Channel::acquireChannel() {
    std::lock_guard lock {_channelLock};

    int firstFreeSlot = __builtin_ctz(_channelSlots);
    if (_channelSlots == 0 || firstFreeSlot >= RMT_CHANNEL_MAX) {
        // All channels occupied
        throw std::runtime_error("All RMT channels occupied.");
    }

    _channelSlots ^= 1 << firstFreeSlot;

    return static_cast<rmt_channel_t>(firstFreeSlot);
}

void Channel::releaseChannel(rmt_channel_t channel) {
    std::lock_guard lock { _channelLock };

    rmt_channel_t rmtChannel = channel;
    _channelSlots |= 1 << rmtChannel;
}

Channel::Channel(gpio_num_t gpio, rmt_channel_t channel) : _channel(channel) {
    rmt_config_t config = RMT_DEFAULT_CONFIG_TX(gpio, _channel);
    config.tx_config.carrier_en = true;
    ESP_ERROR_CHECK(rmt_driver_install(_channel, 0, 0));
    ESP_ERROR_CHECK(rmt_config(&config));

    uint32_t clockHz;
    rmt_get_counter_clock(_channel, &clockHz);
    _clockMHz = (float)clockHz / 1e6;
}

Channel::Channel(Channel &&other) noexcept
    : _channel(std::exchange(other._channel, RMT_CHANNEL_MAX)),
      _clockMHz(other._clockMHz) {}

Channel::~Channel() {
    if (_channel != RMT_CHANNEL_MAX) {
        releaseChannel(_channel);
        ESP_ERROR_CHECK(rmt_driver_uninstall(_channel));
    }
}

void Channel::execute(rmt_item32_t *commandData, std::size_t commandSize) {
//    for (int i = 0; i < commandSize; i++) {
//        std::cout << commandData[i].level0 << " " << commandData[i].duration0 << "; " << commandData[i].level1 << " " << commandData[i].duration1 << std::endl;
//    }
    rmt_write_items(_channel, commandData, commandSize, true);
}

}
