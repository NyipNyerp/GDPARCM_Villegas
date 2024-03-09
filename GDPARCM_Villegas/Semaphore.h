#pragma once
#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(int count = 1);
    ~Semaphore() = default;

    void acquire();
    void release();

private:
    std::mutex mutex;
    std::condition_variable condition;
    int count;
};