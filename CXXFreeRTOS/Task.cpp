#include "Task.hpp"

namespace FreeRTOS {

Task::Task(const char *name, UBaseType_t priority, const std::uint32_t stackSize) {
    xTaskCreate(
            &Task::taskCallback,
            name,
            stackSize,
            this,
            priority,
            &handle);
}

Task::~Task() {
    vTaskDelete(handle);
}

void Task::taskCallback(void *data) {
    auto *task = static_cast<Task *>(data);
    task->task();
}

} // FreeRTOS