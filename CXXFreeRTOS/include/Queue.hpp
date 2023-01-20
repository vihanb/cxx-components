#ifndef FREERTOS_QUEUE_HPP
#define FREERTOS_QUEUE_HPP

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <optional>
#include <type_traits>

namespace FreeRTOS {

template<class T, std::size_t QueueSize = 1>
class Queue final {
private:
    alignas(T) uint8_t data[sizeof(T) * QueueSize];
    StaticQueue_t _queue;

public:
    QueueHandle_t handle;

    Queue() {
        handle = xQueueCreateStatic(QueueSize, sizeof(T), data, &_queue);
    }

    ~Queue() {
        vQueueDelete(handle);
    }

    std::optional<T> receive(TickType_t ticksToWait = portMAX_DELAY) {
        uint8_t result[sizeof(T)];
        if (xQueueReceive(handle, &result, ticksToWait) == pdTRUE) {
            return std::optional(std::move(*reinterpret_cast<T *>(result)));
        } else {
            return std::nullopt;
        }
    }

    void overwrite(const T& value) {
        alignas(T) uint8_t buffer[sizeof(T)];
        T *valueCopy = new (buffer) T(value);
        xQueueOverwrite(handle, valueCopy);
    }
};

}

#endif //FREERTOS_QUEUE_HPP
