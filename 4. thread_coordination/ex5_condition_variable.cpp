#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

std::queue<int> dataQueue;
std::mutex mtx;
std::condition_variable cv;
bool finished = false;

void producer()
{
    for (int i = 1; i <= 5; ++i)
    {
        {
            // Produce data holding the lock
            std::lock_guard<std::mutex> lock(mtx);
            dataQueue.push(i);
            std::cout << "Produced: " << i << std::endl;
        } // Release mutex - no longer needed

        cv.notify_one(); // Notify consumer
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        finished = true;
    }
    cv.notify_one(); // Notify consumer to terminate
}

void consumer()
{
    while (true)
    {
        // Wait until condition fulfilled
        // Mutex protects shared data in condition check
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !dataQueue.empty() || finished; });

        // Read data keeping mutex locked
        while (!dataQueue.empty())
        {
            int value = dataQueue.front();
            dataQueue.pop();
            std::cout << "Consumed: " << value << std::endl;
        }

        if (finished)
            break;
    }
}

int main()
{
    std::jthread producerThread(producer);
    std::jthread consumerThread(consumer);
}
