#include "../util/print.hpp"
#include <semaphore>
#include <thread>
#include <vector>

constexpr int MAX_CONCURRENT_THREADS = 3; // Max allowed concurrent threads

std::counting_semaphore<MAX_CONCURRENT_THREADS> semaphore(MAX_CONCURRENT_THREADS);

void worker(int id)
{
    semaphore.acquire(); // Acquire a slot

    print("Thread ", id, " is working");
    std::this_thread::sleep_for(std::chrono::seconds(id)); // Simulate work
    print("Thread ", id, " is finished");

    semaphore.release(); // Release the slot
}

int main()
{
    constexpr int numThreads = 5;
    std::vector<std::jthread> threads;

    for (int i = 1; i <= numThreads; ++i)
    {
        threads.emplace_back(worker, i);
    }
}
