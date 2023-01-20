#include "EventGroup.hpp"

namespace FreeRTOS {

EventGroup::EventGroup() {
    handle = xEventGroupCreateStatic(&groupData);
}

EventGroup::~EventGroup() {
    vEventGroupDelete(handle);
}

void EventGroup::setBits(EventBits_t bits) {
    xEventGroupSetBits(handle, bits);
}

void EventGroup::waitForAny(EventBits_t bits, bool clearBits, TickType_t timeout) {
    xEventGroupWaitBits(handle,
                        bits,
                        clearBits,
                        false,
                        portMAX_DELAY);
}

void EventGroup::waitForAll(EventBits_t bits, bool clearBits, TickType_t timeout) {
    xEventGroupWaitBits(handle,
                        bits,
                        clearBits,
                        true,
                        portMAX_DELAY);
}

}