#include "../util/print.hpp"
#include <barrier>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

// Number of worker threads
constexpr int num_threads = 3;

// Barrier to synchronize threads at each stage
std::barrier sync_point(num_threads,
                        []() { print("=== All threads reached the barrier, proceeding to next stage ==="); });

void worker(int id)
{
    print("Processing stage 1");
    // ...
    sync_point.arrive_and_wait();

    print("Processing stage 2");
    // ...
    sync_point.arrive_and_wait();

    print("Processing stage 3");
    // ...
    sync_point.arrive_and_wait();
}

int main()
{
    std::vector<std::jthread> threads;
    for (int i = 1; i <= num_threads; ++i)
    {
        threads.emplace_back(worker, i);
    }
}
