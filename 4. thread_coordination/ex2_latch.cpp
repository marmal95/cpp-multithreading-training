#include <iostream>
#include <latch>
#include <thread>
#include <vector>

constexpr int num_threads = 3;
std::latch startup_latch(1);

void worker(int id)
{
    std::cout << "Thread " << id << " waiting for initialization...\n";
    startup_latch.wait();
    std::cout << "Thread " << id << " started working!\n";
}

int main()
{
    std::vector<std::jthread> threads;
    for (int i = 0; i < num_threads; ++i)
    {
        threads.emplace_back(worker, i);
    }

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate setup time
    std::cout << "Main thread: Initialization complete, releasing workers.\n";

    startup_latch.count_down();
}
