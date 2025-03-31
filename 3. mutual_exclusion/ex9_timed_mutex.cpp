#include <iostream>
#include <mutex>
#include <thread>

std::timed_mutex mutex;

void worker(int id)
{
    using namespace std::chrono_literals;

    while (true)
    {
        if (mutex.try_lock_for(100ms))
        { // Try to lock for 100ms
            std::cout << "Thread " << id << " acquired the lock.\n";
            //
            std::this_thread::sleep_for(1s); // Simulate work
            //
            mutex.unlock();
            break; // Exit loop after successful execution
        }
        else
        {
            std::cout << "Thread " << id << " couldn't acquire the lock, retrying...\n";
        }
    }
}

int main()
{
    std::jthread t1(worker, 1);
    std::jthread t2(worker, 2);
}
