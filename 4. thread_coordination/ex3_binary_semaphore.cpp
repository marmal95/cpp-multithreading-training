#include "../util/print.hpp"
#include <semaphore>
#include <thread>
#include <vector>

// Initialized with 0/1 means unavailable/available
std::binary_semaphore semaphore{0};

void worker(int id)
{
    print("Thread ", id, " waiting for access...");
    semaphore.acquire();

    print("Thread ", id, " entered critical section");
    std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Simulate work

    semaphore.release();
    print("Thread ", id, " leaving critical section.");
}

int main()
{
    constexpr int num_threads = 3;
    std::vector<std::jthread> threads;

    for (int i = 0; i < num_threads; ++i)
    {
        threads.emplace_back(worker, i);
    }

    print("Main thread allowing for access");
    semaphore.release();
}
