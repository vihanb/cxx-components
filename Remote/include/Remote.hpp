#pragma once
#include <driver/rmt.h>
#include <unordered_map>

namespace Remote {

using Bit = std::pair<bool, uint32_t>;

template<std::size_t Size>
using CompiledCommand = std::array<rmt_item32_t, Size>;

class Channel {
private:
    rmt_channel_t _channel;
    float _clockMHz;

public:
    Channel(gpio_num_t gpio);
    Channel(Channel&&);
    virtual ~Channel();

    Channel() = delete;
    Channel(const Channel&) = delete;

    template<std::size_t Size>
    CompiledCommand<(Size + 1) / 2> toTickedCommand(
        std::array<Bit, Size> command
    ) const {
        CompiledCommand<(Size + 1) / 2> res;

        for (int i = 0; i < command.size(); i++) {
            if (i % 2 == 0) {
                res[i / 2].duration0 = (uint32_t)(command[i].second * _clockMHz);
                res[i / 2].level0 = command[i].first;
            } else {
                res[i / 2].duration1 = (uint32_t)(command[i].second * _clockMHz);
                res[i / 2].level1 = command[i].first;
            }
        }

        return res;
    }

    void execute(rmt_item32_t *commandData, std::size_t commandSize);

    template<std::size_t Size>
    void execute(CompiledCommand<Size> command) {
        execute(command.data(), command.size());
    }

    template<std::size_t Size>
    void execute(std::array<std::pair<bool, uint32_t>, Size> command) {
        execute(toTickedCommand(command));
    }
};

}