#pragma once
#include <hap.h>
#include "homekit_value.hpp"

namespace HomeKit {

class Characteristic {
public:
    hap_char_t *hapChar;

    Characteristic() = delete;
    Characteristic(hap_char_t *hapChar);

    const char *typeUUID() const;
    bool isTypeUUID(const char *typeUUID) const;
    
    hap_char_format_t format() const;
    void value(const Value &newValue);
    Value value() const;

    Characteristic& operator=(const Value &newValue);
};

}