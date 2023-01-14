#pragma once
#include <hap.h>
#include "homekit_value.hpp"

namespace HomeKit {

class Characteristic {
public:
    hap_char_t *hapChar;

    Characteristic() = delete;
    Characteristic(hap_char_t *hapChar);

    static Characteristic fromUUID(const char *UUID);

    const char *typeUUID() const;
    bool isTypeUUID(const char *typeUUID) const;
    
    hap_char_format_t format() const;
    void value(const Value &newValue) const;
    Value value() const;

    Characteristic& operator=(const Value &newValue);
};

}