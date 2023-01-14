#pragma once
#include "Remote.hpp"
#include <cstdint>

namespace Remote::Lasko {

namespace Command {
    constexpr int TICKS = 3;
    constexpr uint32_t INITIAL_PULSE = 7000;
    constexpr uint32_t SHORT_TIME = 440;
    constexpr uint32_t LONG_TIME = 3 * 440;

    using LaskoCommand = std::array<Symbol, 25>;
    constexpr LaskoCommand toLaskoSymbols(uint16_t command) {
        LaskoCommand symbols;
        symbols[0].first = 1;
        symbols[1].second = INITIAL_PULSE;

        for (int i = 0; i < 12; i++) {
            if (command & 1) {
                symbols[i * 2 + 0].first = 0;
                symbols[i * 2 + 0].second = SHORT_TIME;
                symbols[i * 2 + 1].first = 1;
                symbols[i * 2 + 1].second = LONG_TIME;
            } else {
                symbols[i * 2 + 0].first = 0;
                symbols[i * 2 + 0].second = LONG_TIME;
                symbols[i * 2 + 1].first = 1;
                symbols[i * 2 + 1].second = SHORT_TIME;
            }

            command >>= 1;
        }

        return symbols;
    }

    constexpr LaskoCommand TOGGLE_POWER = toLaskoSymbols(0b0010'0111'1110);
    constexpr LaskoCommand TOGGLE_SWING = toLaskoSymbols(0b0010'0111'1110);
    constexpr LaskoCommand SPEED = toLaskoSymbols(0b0010'0111'1110);
}

class LaskoChannel : public Remote::Channel {
private:

public:
    using LaskoCompiledCommand = Remote::CompiledCommand<13>;
    
    const LaskoCompiledCommand togglePower = toTickedCommand(Command::TOGGLE_POWER);
    const LaskoCompiledCommand toggleSwing = toTickedCommand(Command::TOGGLE_SWING);
    const LaskoCompiledCommand speed = toTickedCommand(Command::SPEED);

    LaskoChannel(gpio_num_t gpio) : Remote::Channel(gpio) {};
};

}