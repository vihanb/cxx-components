#ifndef FREERTOS_EVENTGROUP_HPP
#define FREERTOS_EVENTGROUP_HPP

#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>

namespace FreeRTOS {

class EventGroup {
private:
    StaticEventGroup_t groupData;

public:
    EventGroupHandle_t handle;

    EventGroup();
    virtual ~EventGroup();

    EventGroup(EventGroup&&) = delete;
    EventGroup(const EventGroup&) = delete;

    void setBits(EventBits_t bits);

    void waitForAny(EventBits_t bits, bool clearBits = false, TickType_t timeout = portMAX_DELAY);
    void waitForAll(EventBits_t bits, bool clearBits = false, TickType_t timeout = portMAX_DELAY);
};

}

#endif //FREERTOS_EVENTGROUP_HPP
