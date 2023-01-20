#pragma once
#include <string>
#include <esp_event.h>
#include <CXXFreeRTOS.hpp>

class WiFi {
private:
    std::string serviceName;
    uint32_t popSeed;

    FreeRTOS::EventGroup wifiEventGroup;

    void handler(esp_event_base_t event_base, int32_t event_id, void* event_data);
    static void eventHandler(
        void *data,
        esp_event_base_t event_base,
        int32_t event_id, void* event_data);

    void printQRCode();

public:
    explicit WiFi(const std::string &serviceName);
    ~WiFi();

    // Unique device name.
    std::string deviceName();

    // Secure random POP string.
    std::string pop();

    void init();
    void start();
};