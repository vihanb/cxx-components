#pragma once
#include <driver/rmt.h>
#include <unordered_map>
#include <mutex>

namespace Remote {

/**
 * @brief A transmission symbol in us.
 * Represents a boolean (HIGH or LOW) symbol for a specified
 * amount of time in microseconds.
 */
using Symbol = std::pair<bool, uint32_t>;

/**
 * @brief Channel-specific transmission command.
 * A sequence of symbols that has had its channel-specific
 * time-to-tick conversion completed. 
 */
template<std::size_t Size>
using CompiledCommand = std::array<rmt_item32_t, Size>;

class Channel {
private:
    rmt_channel_t _channel;
    float _clockMHz;

private:
    static rmt_channel_t acquireChannel();
    static void releaseChannel(rmt_channel_t channel);

public:
    explicit Channel(gpio_num_t gpio, rmt_channel_t channel = acquireChannel());
    Channel(Channel&&) noexcept;
    virtual ~Channel();

    Channel() = delete;
    Channel(const Channel&) = delete;

    /**
     * @brief Creates a CompiledCommand.
     * If your command is well-known beforehand. Use this to
     * avoid needing to allocate and compile a command every
     * time it is executed.
     * 
     * @tparam Size 
     * @param command unretained series of symbols.
     * @return CompiledCommand<(Size + 1) / 2> 
     */
    template<std::size_t Size>
    CompiledCommand<(Size + 1) / 2> toTickedCommand(
        std::array<Symbol, Size> command
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