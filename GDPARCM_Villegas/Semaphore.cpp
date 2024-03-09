#include "Semaphore.h"

Semaphore::Semaphore(int count)
{
    this->count = count;
}

void Semaphore::acquire() {
    std::unique_lock<std::mutex> lock(mutex);
    condition.wait(lock, [this] { return count > 0; }); 
    --count;
}

void Semaphore::release() {
    std::lock_guard<std::mutex> lock(mutex);
    ++count;
    condition.notify_one();
}