#include <iostream>
#include <mutex>
#include <thread>

std::recursive_mutex rmtx;
int counter = 0;

void recursiveFunction(int depth)
{
    if (depth <= 0)
        return;

    rmtx.lock(); // Lock the mutex (same thread can lock multiple times)
    std::cout << "Thread " << std::this_thread::get_id() << " entered depth " << depth << "\n";
    counter++;

    recursiveFunction(depth - 1); // Recursive call with the same lock held

    std::cout << "Thread " << std::this_thread::get_id() << " leaving depth " << depth << "\n";
    rmtx.unlock(); // Unlock once for each lock
}

int main()
{
    std::thread t1(recursiveFunction, 3); // Start a thread that calls a recursive function
    std::thread t2(recursiveFunction, 3); // Start another thread doing the same

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter << "\n";
    return 0;
}
