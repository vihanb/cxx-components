#pragma once
#include <hap.h>
#include <string>
#include <esp_log.h>

#include "homekit_value.hpp"

namespace HomeKit {

class Value {
    static constexpr const char *formatToString(hap_char_format_t format) {
        switch (format) {
            case HAP_CHAR_FORMAT_NONE: return "None";
            case HAP_CHAR_FORMAT_BOOL: return "bool";
            case HAP_CHAR_FORMAT_UINT8: return "uint8_t";
            case HAP_CHAR_FORMAT_UINT16: return "uint16_t";
            case HAP_CHAR_FORMAT_UINT32: return "uint32_t";
            case HAP_CHAR_FORMAT_UINT64: return "uint64_t";
            case HAP_CHAR_FORMAT_INT: return "int";
            case HAP_CHAR_FORMAT_FLOAT: return "float";
            case HAP_CHAR_FORMAT_STRING: return "string";
            case HAP_CHAR_FORMAT_TLV8: return "tlv8";
            case HAP_CHAR_FORMAT_DATA: return "[[data]]";
            default: return "[[unknown]]";
        }
    }

public:

    const hap_val_t value;
    const hap_char_format_t knownFormat;
    
    void validateAs(hap_char_format_t expectedFormat) const;

    Value() = delete;
    Value(const hap_val_t value, hap_char_format_t format = HAP_CHAR_FORMAT_NONE);
    
    Value(bool);
    Value(uint8_t);
    Value(uint32_t);
    Value(uint64_t);
    Value(float);
    Value(const std::string&);

    operator bool() const;
    operator int() const;
    operator uint8_t() const;
    operator uint32_t() const;
    operator uint64_t() const;
    operator float() const;
    operator std::string() const;
};

}