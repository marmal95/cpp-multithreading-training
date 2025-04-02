#include "../util/print.hpp"
#include <atomic>
#include <semaphore>
#include <thread>

std::atomic<int> counter{};
std::binary_semaphore pingSem{1};
std::binary_semaphore pongSem{0};

constexpr int limit = 10;

void runPing()
{
    while (counter < limit)
    {
        pingSem.acquire();
        counter++;
        print("Ping: ", counter);
        pongSem.release();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate work
    }
}

void runPong()
{
    while (counter < limit)
    {
        pongSem.acquire();
        print("Pong: ", counter);
        pingSem.release();
    }
}

int main()
{
    std::jthread pingThread(runPing);
    std::jthread pongThread(runPong);
}
