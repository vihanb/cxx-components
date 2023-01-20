#include "Task.hpp"

namespace FreeRTOS {

Task::Task(const char *name, const std::uint32_t stackSize, UBaseType_t priority) {
    xTaskCreate(
            &Task::taskCallback,
            "Fan Controller Handler",
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