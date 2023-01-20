#ifndef FREERTOS_TASK_HPP
#define FREERTOS_TASK_HPP

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <cstdint>

namespace FreeRTOS {

class Task {
private:
    static void taskCallback(void *data);

protected:
    TaskHandle_t handle;
    Task(const char *name, std::uint32_t stackSize = 4096, UBaseType_t priority = 5);

public:
    virtual ~Task();

    [[noreturn]] virtual void task() = 0;
};

} // FreeRTOS

#endif //FREERTOS_TASK_HPP
